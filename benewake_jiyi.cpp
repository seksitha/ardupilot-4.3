#include <AP_HAL/AP_HAL.h>
#include <AP_BoardConfig/AP_BoardConfig.h>
#include "AP_RangeFinder_Benewake_CAN.h"

#if HAL_MAX_CAN_PROTOCOL_DRIVERS
using namespace AP_HAL;

extern const AP_HAL::HAL &hal;
const AP_Param::GroupInfo AP_RangeFinder_Benewake_CAN::var_info[] = {

    // @Param: RECV_ID
    // @DisplayName: CAN receive ID
    // @Description: The receive ID of the CAN frames. A value of zero means all IDs are accepted.
    // @Range: 0 65535
    // @User: Advanced
    AP_GROUPINFO("RECV_ID", 10, AP_RangeFinder_Benewake_CAN, receive_id, 0),

    // @Param: SNR_MIN
    // @DisplayName: Minimum signal strength
    // @Description: Minimum signal strength (SNR) to accept distance
    // @Range: 0 65535
    // @User: Advanced
    AP_GROUPINFO("SNR_MIN", 11, AP_RangeFinder_Benewake_CAN, snr_min, 0),

    AP_GROUPEND
};

Benewake_MultiCAN *AP_RangeFinder_Benewake_CAN::multican;

/*
  constructor
 */
AP_RangeFinder_Benewake_CAN::AP_RangeFinder_Benewake_CAN(RangeFinder::RangeFinder_State &_state, AP_RangeFinder_Params &_params) :
    AP_RangeFinder_Backend(_state, _params)
{
    if (multican == nullptr) {
        multican = new Benewake_MultiCAN();
        if (multican == nullptr) {
            AP_BoardConfig::allocation_error("Benewake_CAN");
        }
    }

    {
        // add to linked list of drivers
        WITH_SEMAPHORE(multican->sem);
        auto *prev = multican->drivers;
        next = prev;
        multican->drivers = this;
    }

    AP_Param::setup_object_defaults(this, var_info);
    state.var_info = var_info;
}

// update state
void AP_RangeFinder_Benewake_CAN::update(void)
{
    WITH_SEMAPHORE(_sem);
    const uint32_t now = AP_HAL::millis();
    if (_distance_count == 0 && now - state.last_reading_ms > 500) {
        // no new data.
        set_status(RangeFinder::Status::NoData);
    } else if (_distance_count != 0) {
        state.distance_m = 0.01 * (_distance_sum_cm / _distance_count);
        state.last_reading_ms = AP_HAL::millis();
        _distance_sum_cm = 0;
        _distance_count = 0;
        update_status();
    }
}

// handler for incoming frames. These come in at 100Hz
bool AP_RangeFinder_Benewake_CAN::handle_frame(AP_HAL::CANFrame &frame)
{
    WITH_SEMAPHORE(_sem);
    const uint16_t id = frame.id & AP_HAL::CANFrame::MaskStdID;
    if (receive_id != 0 && id != uint16_t(receive_id.get())) {
        // incorrect receive ID
        return false;
    }
    if (last_recv_id != -1 && id != last_recv_id) {
        // changing ID
        return false;
    }
    last_recv_id = id;

    const uint16_t dist_cm = (frame.data[5]);
    const uint16_t cksum = (frame.data[3]+frame.data[4]+frame.data[5]+frame.data[6]) ;
    
    if ((cksum) == frame.data[7]) {
        // too low signal strength
        _distance_sum_cm += dist_cm ;
        _distance_count++;
        return true;
    }

    // hal.console->printf("d0 0x%02hhx \n", frame.data[0]); //5A
    // hal.console->printf("d1 0x%02hhx \n", frame.data[1]); //A5
    // hal.console->printf("d2 0x%02hhx \n", frame.data[2]); //len
    // hal.console->printf("d3 0x%02hhx \n", frame.data[3]); //0xf3 can_l
    // hal.console->printf("d1 %f \n", _distance_sum_cm);
    // hal.console->printf("d4 0x%02hhx \n", frame.data[4]); //0x00 can_h
    // hal.console->printf("d5 0x%02hhx \n", frame.data[5]); //0x3f dbf
    // hal.console->printf("d6 0x%02hhx \n", frame.data[6]); //0x00 resv
    // hal.console->printf("d7 0x%02hhx \n", frame.data[7]); //0x32 cksum 0xf3+0x00+0x3f=0x32

    return false;
}

// handle frames from CANSensor, passing to the drivers
void Benewake_MultiCAN::handle_frame(AP_HAL::CANFrame &frame)
{
    WITH_SEMAPHORE(sem);
    for (auto *d = drivers; d; d=d->next) {
        if (d->handle_frame(frame)) {
            break;
        }
    }
}

#endif // HAL_MAX_CAN_PROTOCOL_DRIVERS

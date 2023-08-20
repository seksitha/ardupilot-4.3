// user defined variables

// example variables used in Wii camera testing - replace with your own
// variables
#ifdef USERHOOK_VARIABLES

#include <AP_Common/AP_Common.h>            // Common definitions and utility routines for the ArduPilot libraries
#include <AP_Common/Location.h>             // Library having the implementation of location class         
#include "GCS_Mavlink.h"

class UserCode {

    public:
        UserCode() = default;
         uint8_t chan_pump;
         uint8_t chan_spinner;
        bool pump_off_on_boot = false;
         uint16_t rc6_pwm;
         uint16_t rc8_pwm;
        uint16_t current_mission_length;
        uint16_t current_mission_index;
        uint8_t sensor_loop_index = 0;
        uint8_t flow_loop_counter = 0;
        uint16_t flow_value = 0;
        uint8_t mission_timer_not_to_monitor_flow_at_start_waypoint = 0;
        uint8_t flow_index = 0;
        bool spray_at_16_even = false;
        bool auto_has_been_on_rngfnd = false;
        Location mission_breakpoint;
        mavlink_mission_item_int_t current_mission_waypoint_finish_point;
        
        bool alert_empty_tank = false;
        int16_t cmd_16_index = 0;
        void set_pump_spinner_pwm(bool spray_state);
};


#endif  // USERHOOK_VARIABLES



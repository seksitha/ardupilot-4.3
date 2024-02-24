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
        uint8_t chan_spinner2;
        uint8_t chan_spinner3;
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
        int8_t number_switch_to_rngfnd = 0;
        int32_t takeoff_baro_offset =0;
        float theta_alt_wp = 0;
        float next_theta_alt_wp = 0;
        bool is_origin_set = false;
        bool is_home_set = false;
        bool spray_at_16_even = false;
        bool is_on_rngfnd = false;
        // float alt_transit_offset = 0;
        float _alt_offset_gps_alt;
        float _alt_transit_to_gps;
        float _alt_transit_to_rngfnd;
        bool can_switch_to_rngfnd = false;
        bool transit_to_loiter = false;
        bool takeoff_done = false;
        // bool reset_target_to_gps = false;
        Location mission_breakpoint;
        mavlink_mission_item_int_t current_mission_waypoint_finish_point;
        
        bool alert_empty_tank = false;
        int16_t cmd_16_index = 0;
        bool is_print_break_auto = false;
        void set_pump_spinner_pwm(bool spray_state);
};


#endif  // USERHOOK_VARIABLES



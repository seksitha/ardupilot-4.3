
#include "Copter.h"

void UserCode::set_pump_spinner_pwm(bool spray_state){
    if( spray_state == false) {
        SRV_Channels::set_output_pwm_chan( chan_pump , 1000);
        SRV_Channels::set_output_pwm_chan( chan_spinner , 1000);
        //gcs().send_text(MAV_SEVERITY_INFO, "spray off");
    }
    if(spray_state == true){
        if(copter.wp_nav->_radio_type == 12){
<<<<<<< Updated upstream
            SRV_Channels::set_output_pwm_chan( chan_pump , RC_Channels::get_radio_in(5) > 1080 ? copter.wp_nav->_pwm_pump < 100 ? copter.wp_nav->_pwm_pump*10+1000 : 1950 : 1000);
            SRV_Channels::set_output_pwm_chan( chan_spinner , rc8_pwm = RC_Channels::get_radio_in(7) > 1080 ? copter.wp_nav->_pwm_nozzle < 100 ? copter.wp_nav->_pwm_nozzle *10+1000: 1950 : 1000 );
        }else{
            if (rc6_pwm != RC_Channels::get_radio_in(5) or rc8_pwm != RC_Channels::get_radio_in(7) ){
                rc6_pwm = RC_Channels::get_radio_in(5);
                rc8_pwm = RC_Channels::get_radio_in(7) > copter.wp_nav->_pwm_nozzle*10+1000 ? copter.wp_nav->_pwm_nozzle*10+1000 : RC_Channels::get_radio_in(7);
=======

            if(RC_Channels::get_radio_in(5) > 1600){
                rc6_pwm =  copter.wp_nav->_pwm_pump < 60 ? (copter.wp_nav->_pwm_pump + 30) * 10 + 1000 : 2000;
            }
            else if(RC_Channels::get_radio_in(5) > 1150 && RC_Channels::get_radio_in(5) < 1550 ){
                rc6_pwm = (copter.wp_nav->_pwm_pump + 15) * 10 + 1000;
            }
            else if (RC_Channels::get_radio_in(5) < 1150){
                 rc6_pwm = 1000;
            } 
            SRV_Channels::set_output_pwm_chan( chan_pump , rc6_pwm);
            SRV_Channels::set_output_pwm_chan( chan_spinner , rc8_pwm = RC_Channels::get_radio_in(7) > 1080 ? copter.wp_nav->_pwm_nozzle < 100 ? copter.wp_nav->_pwm_nozzle *10+1000: 1950 : 1000 );

        }else{
            if (rc6_pwm != RC_Channels::get_radio_in(5) or rc8_pwm != RC_Channels::get_radio_in(7) ){
                rc6_pwm = RC_Channels::get_radio_in(5);
                rc8_pwm = RC_Channels::get_radio_in(7) > (copter.wp_nav->_pwm_nozzle*10) + 1000 ? copter.wp_nav->_pwm_nozzle*10+1000 : RC_Channels::get_radio_in(7);
>>>>>>> Stashed changes
            }
            SRV_Channels::set_output_pwm_chan( chan_pump , rc6_pwm);
            SRV_Channels::set_output_pwm_chan( chan_spinner , rc8_pwm);    
        }

        //gcs().send_text(MAV_SEVERITY_INFO, "spray on");
    }
}
#ifdef USERHOOK_INIT
void Copter::userhook_init()
{
    // put your initialisation code here
    // this will be called once at start-up
}
#endif

#ifdef USERHOOK_FASTLOOP
void Copter::userhook_FastLoop()
{
    // put your 100Hz code here
}
#endif

#ifdef USERHOOK_50HZLOOP
void Copter::userhook_50Hz()
{
    // put your 50Hz code here
}
#endif

#ifdef USERHOOK_MEDIUMLOOP
void Copter::userhook_MediumLoop()
{
    // put your 10Hz code here
}
#endif

#ifdef USERHOOK_SLOWLOOP
void Copter::userhook_SlowLoop()
{
    // put your 3.3Hz code here



    /*FLOWSENSOR */
    if(get_mode()==3 && userCode.cmd_16_index > 1){
        // not to trigger the flow sensor at the beginning of the mission.
<<<<<<< Updated upstream
        
=======
        userCode.is_print_break_auto = false;
>>>>>>> Stashed changes
        uint8_t delay_monitor_flow = 6; // base on loop frequency we want to delay 2 second. 
        if (userCode.cmd_16_index % 2 != 0) { //mission 2 is the start spray so index is 1 we reset the monitor flow
            userCode.mission_timer_not_to_monitor_flow_at_start_waypoint = 0;
            return;
        }
        //mission 3 is the start spray so index is 2 we delay some time before tricker the empty tank
        if( userCode.cmd_16_index % 2 == 0  && userCode.mission_timer_not_to_monitor_flow_at_start_waypoint < delay_monitor_flow) {
            userCode.mission_timer_not_to_monitor_flow_at_start_waypoint = userCode.mission_timer_not_to_monitor_flow_at_start_waypoint + 1;
            // gcs().send_text(MAV_SEVERITY_INFO, "count %i",userCode.mission_timer_not_to_monitor_flow_at_start_waypoint);
            return;
        }

        // gcs().send_text(MAV_SEVERITY_INFO, "check %i",userCode.cmd_16_index);
        // if empty tank stop copter
        if (userCode.mission_timer_not_to_monitor_flow_at_start_waypoint >= delay_monitor_flow && RC_Channels::get_radio_in(6) > 1400 ){  //radio chan7 > 1400
            uint16_t flow_val = hal.gpio->read(copter.wp_nav->_sensor_pin); // nano  v5
            // uint16_t flow_val = hal.gpio->read(54); //       v5+
            userCode.flow_value = userCode.flow_value + flow_val ;
            // userCode.flow_value =  userCode.flow_value + flow_val;
            uint8_t loop_counter_max = 4;
            if ( userCode.flow_index >= loop_counter_max) {
                if ( RC_Channels::get_radio_in(9) > 1400){
                    gcs().send_text(MAV_SEVERITY_INFO, "flow val %i %i", userCode.flow_value/5, flow_val);
                }
                if ((userCode.flow_value/(loop_counter_max+1)) == 1 && !userCode.alert_empty_tank ){
                    gcs().send_text(MAV_SEVERITY_CRITICAL, "Water Tank Empty");
                    copter.set_mode(Mode::Number::LOITER, ModeReason::GCS_COMMAND);
                    userCode.alert_empty_tank = true;
                }
                userCode.flow_value = 0;
            }

            userCode.flow_index = userCode.flow_index >= loop_counter_max ? 0 : userCode.flow_index+1;

        }
    }

    // gcs().send_text(MAV_SEVERITY_INFO, "_______missionState %i ",mode_auto.mission.state());
<<<<<<< Updated upstream
    /*(Done) misison complete loiter and stop spray*/ 
=======
    /*(Done) misison complete loiter and stop spray
    // mission complete only call when all mission has been flow , no jump allow.
    */ 
>>>>>>> Stashed changes
    if(mode_auto.mission.state() == 2 and copter.wp_nav->loiter_state_after_mission_completed == false && copter.get_mode()==3 && motors->armed()){
        copter.set_mode(Mode::Number::LOITER, ModeReason::GCS_COMMAND);
        userCode.set_pump_spinner_pwm(false);   
        copter.wp_nav->loiter_state_after_mission_completed = true;
<<<<<<< Updated upstream
=======
        gcs().send_text(MAV_SEVERITY_INFO, "# Mission Complete");
>>>>>>> Stashed changes
    }
    // stop spray on RTL when has water
    if(copter.get_mode()==6 && motors->armed()){
        userCode.set_pump_spinner_pwm(false);   
    }
    // 
}
#endif

#ifdef USERHOOK_SUPERSLOWLOOP
void Copter::userhook_SuperSlowLoop()
{
    // put your 1Hz code here
        // SPRAY speed update
    if(!userCode.chan_pump){
        SRV_Channels::find_channel(SRV_Channel::k_sprayer_pump,userCode.chan_pump);
    }
    if(!userCode.chan_spinner){
        SRV_Channels::find_channel(SRV_Channel::k_sprayer_spinner,userCode.chan_spinner);
        // gcs().send_text(MAV_SEVERITY_INFO, "sitha: =>chanel_pum %i", userCode.chan_spinner);
    }
    //​ Avoid calibrate pump esc
    if(RC_Channels::get_radio_in(6) /*chanel 7 switch*/ < 1600 && !userCode.pump_off_on_boot){
        userCode.pump_off_on_boot = true;
    }
    // switch the pump on by RC
    if (copter.get_mode()!=3 /*not auto*/ && userCode.chan_pump && userCode.chan_spinner && userCode.pump_off_on_boot){
        if (RC_Channels::get_radio_in(6) > 1550){
            uint16_t flow_val = hal.gpio->read(copter.wp_nav->_sensor_pin); // nano  v5 pin 60
            // uint16_t flow_val = hal.gpio->read(54); //       v5+
            if(flow_val == 0){
                userCode.set_pump_spinner_pwm(true);
            }else{
                userCode.set_pump_spinner_pwm(false); 
            }
        } else {
            userCode.set_pump_spinner_pwm(false);         
        }
    }

        // read value of level sensor
    if (RC_Channels::get_radio_in(9) > 1500){
        //uint16_t flow_val = copter.wp_nav->readFlowSensor(60);
        uint16_t flow_val = hal.gpio->read(copter.wp_nav->_sensor_pin); // nano  v5
        // uint16_t flow_val = hal.gpio->read(54); //       v5+

        if (userCode.sensor_loop_index >= 2){
            gcs().send_text(MAV_SEVERITY_INFO, "Sensor %s", flow_val==0? "on":"off");
            userCode.sensor_loop_index = 0;
        }
        userCode.sensor_loop_index = userCode.sensor_loop_index + 1;
    }
    
    
    // MISSIONBREAKPOINT code start here.
    if( copter.get_mode() == 3 && mode_auto.mission.mission_uploaded_success_state ){
        mode_auto.mission.mission_uploaded_success_state = false;
        // gcs().send_text(MAV_SEVERITY_INFO, "sitha: => ___________breakpoint hit1");
    }

    /* BREAKPOINT resuming when empty tank*/
    // TEST case A, upload mission -> stop -> continue, stop @ wp 2, 3, 5, 7 then land 
    // hit resume, then fly auto -> hit loiter immediately -> hit auto see where it go.
    // wait till wp 5 -> land -> resume -> download plan
    // TEST case B: fly auto , stop at wp 4 and start again will spray at that point?
    if( !motors->armed() && mode_auto.mission.num_commands() &&  mode_auto.mission.mission_uploaded_success_state == true)
    {   
        // get new mission finish location after resume command hit
        // mavlink_mission_item_int_t new_mission_finish_point ;
        // mode_auto.mission.get_item(mode_auto.mission.num_commands()-1, new_mission_finish_point);
        // // get new mission wapypoint #2 location after resume command hit
        // mavlink_mission_item_int_t new_mission_waypoint_2 ;
        // mode_auto.mission.get_item(2, new_mission_waypoint_2);
        // // gcs().send_text(MAV_SEVERITY_INFO, "sitha: => new %i", new_mission_waypoint_2.x);
        // // gcs().send_text(MAV_SEVERITY_INFO, "sitha: => old %i", userCode.mission_breakpoint.lat);

        // /* WE SET breakpoint only if the end point is the same with new upload plan 
        // and the length is sorter than the old one otherwise we can not upload new mission when 
        // user make mistake*/
        // if( userCode.current_mission_waypoint_finish_point.x == new_mission_finish_point.x && 
        //     userCode.current_mission_waypoint_finish_point.y == new_mission_finish_point.y &&
        //     mode_auto.mission.num_commands() < userCode.current_mission_length )
        // {
        //     // gcs().send_text(MAV_SEVERITY_INFO, "sitha=> resume success %i",mode_auto.cmd_16_index );

        //     // TODO: this algorithm problem at the near of the end wp breakpoint
        //     // float PI = 3.14159265f;
        //     // float R = 6378137.0f; // Sitha: Earth radius in meter
        //     // float half_radian = 180.0f;

        //     // // devide by 10+e7 won't work well but multiply by 0.00000001 work well
        //     // float lat = (float)(copter.wp_nav->origin_for_breakpoint.lat * 0.0000001f) * PI / half_radian; //convert degree to radian
        //     // float lon = (float)(copter.wp_nav->origin_for_breakpoint.lng * 0.0000001f) * PI / half_radian;

        //     // float brng = (float)(copter.wp_nav->wp_bearing)*0.01f * PI / half_radian;
        //     // float d = /*copter.wp_nav->traveled_distance<400 && copter.wp_nav->_fast_turn ? 0.0f :*/  (copter.wp_nav->traveled_distance-70)*0.01f;
        //     // float newLat = asinf(sinf(lat) * cosf(d / R) + cosf(lat) * sinf(d / R) * cosf(brng));
        //     // float newLon = lon + atan2f(sinf(brng) * sinf(d / R) * cosf(lat), cosf(d / R) - sinf(lat) * sinf(newLat));
        //     // float latDegree = newLat * half_radian / PI;
        //     // float lonDegree = newLon * half_radian / PI; // result as radian so convert back to degree
        //     // new_mission_waypoint_2.x = (int32_t)(latDegree*10000000);
        //     // new_mission_waypoint_2.y = (int32_t)(lonDegree*10000000);    
        //     // gcs().send_text(MAV_SEVERITY_INFO, "sitha=> resume lat %f, %f brng %f", (float)(copter.wp_nav->origin_for_breakpoint.lat*.0000001f), (float)(copter.wp_nav->origin_for_breakpoint.lng*0.0000001f),(float)copter.wp_nav->wp_bearing*0.01f);

        //     // TODO: calculate offset lat x metters and offset lng x meters // work well, better than above dont know why.
        //     float R = 6378137.00000000f;
        //     float dlat = copter.wp_nav->_corect_coordinate_ns/R;
        //     float dlon = copter.wp_nav->_corect_coordinate_we/(R*cosf(3.14150000f*(float)userCode.mission_breakpoint.lat/10000000/180.00000000f));
        //     float correct_breakpoint_lat = ((float)userCode.mission_breakpoint.lat/10000000-(dlat*180/3.14150000f));
        //     float correct_breakpoint_lng = ((float)userCode.mission_breakpoint.lng/10000000)-((dlon*180/3.14150000f));
        //     new_mission_waypoint_2.x = int32_t(correct_breakpoint_lat*10000000);
        //     new_mission_waypoint_2.y = (int32_t)(correct_breakpoint_lng*10000000);

        //     // in case pilot stop at the side turn don't set break point QGC will take out this wp
        //     if(userCode.cmd_16_index % 2 == 0 || copter.wp_nav->_spray_all==1){
        //         mode_auto.mission.set_item(2, new_mission_waypoint_2 ); 
        //     } 
        //     // we set this to false so that it is not doing it again and again 
        //     // and when we upload it is not reset out mission
        //     mode_auto.mission.mission_uploaded_success_state = false;
        //     userCode.cmd_16_index= 0; // don't change this will effect resume waypoint at side turn
        //     userCode.current_mission_index = 0;
        // }
    }

    // MISSION break by user and resume / this prevent user fly to somewhere and decide to resume so it resume to breakpoint
    if(mode_auto.mission.get_current_nav_index() > 1 && copter.get_mode()!=3 && motors->armed() && !userCode.is_print_break_auto){
        copter.wp_nav->break_auto_by_user_state = true;
        gcs().send_text(MAV_SEVERITY_INFO,"break_lat %ld", userCode.mission_breakpoint.lat );
        gcs().send_text(MAV_SEVERITY_INFO,"break_lng %ld", userCode.mission_breakpoint.lng );
        gcs().send_text(MAV_SEVERITY_INFO,"break_set" );
        userCode.is_print_break_auto = true;
    }

    // if (motors->armed() && copter.get_mode()!=3 /*not equal auto*/
    //     && mode_auto.mission.state() == 0 
    //     && userCode.current_mission_index >= 3 && copter.wp_nav->break_auto_by_user_state == true)
    // {

        // Stop implement go to breakpoint when user stop or sensor problem. 
        // TODO: should be an option if user wanted to incase sensor problem
        // gcs().send_text(MAV_SEVERITY_INFO, "sitha: => _________breakpoint success");

        // mavlink_mission_item_int_t current_waypoint ;
        // mode_auto.mission.get_item(userCode.current_mission_index-1, current_waypoint);
        // current_waypoint.x = userCode.mission_breakpoint.lat;
        // current_waypoint.y = userCode.mission_breakpoint.lng;
        // mode_auto.mission.set_item(userCode.current_mission_index-1, current_waypoint);
        // mode_auto.mission.set_current_cmd(userCode.current_mission_index-1);
    //     copter.wp_nav->break_auto_by_user_state = false; // help not to set cmd_16_index + 1 so continue spray
    // }

    if(copter.get_mode()!=3 /*not = auto*/ ){
        // mode_auto.cmd_16_index = 0; // set this will make break by user no spray untill land
        if(!motors->armed()) { // prevent on take off set current waypoint the old user break point
            copter.wp_nav->break_auto_by_user_state = false;
            copter.wp_nav->reset_param_on_start_mission();
            copter.wp_nav->loiter_state_after_mission_completed = false;
        }
    }
    // MISSIONBREAKPOINT code end here.
    // 
}
#endif

#ifdef USERHOOK_AUXSWITCH
void Copter::userhook_auxSwitch1(const RC_Channel::AuxSwitchPos ch_flag)
{
    // put your aux switch #1 handler here (CHx_OPT = 47)
}

void Copter::userhook_auxSwitch2(const RC_Channel::AuxSwitchPos ch_flag)
{
    // put your aux switch #2 handler here (CHx_OPT = 48)
}

void Copter::userhook_auxSwitch3(const RC_Channel::AuxSwitchPos ch_flag)
{
    // put your aux switch #3 handler here (CHx_OPT = 49)
}
#endif

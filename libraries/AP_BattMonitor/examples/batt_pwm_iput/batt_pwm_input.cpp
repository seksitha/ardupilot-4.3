#include <AP_HAL/AP_HAL.h>
#include "AP_BattMonitor_FuelLevel_PWM.h"

// we need a boardconfig created so that the io processor is available
#if HAL_WITH_IO_MCU
#include <AP_BoardConfig/AP_BoardConfig.h>
#include <AP_IOMCU/AP_IOMCU.h>
AP_BoardConfig BoardConfig;

void setup();                                                   //This function is defined in most of the libraries. This function is called only once at boot up time. This function is called by main() function in HAL.
void loop();                                                    //This function is defined in most of the libraries. This function is called by main function in HAL. The main work of the sketch is typically in this function only.

const AP_HAL::HAL& hal = AP_HAL::get_HAL(); 


class Batt_pwm_test : public AP_BattMonitor_FuelLevel_PWM{

}

Batt_pwm_test &batt_test();

void setup(){
  hal.console->printf("ArduPilot RC Channel test\n");
  batt_test.init();
}

void loop(){
  batt_test().read();
}
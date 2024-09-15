# QioTek AdeptF404 Flight Controller

The Qiotek AdeptF427 an autopilot produced by [QioTek](https://www.qiotek.io).

It is an autopilot based on CKS MCU chips produced in China.

## Features
 - MCU: NS32F407VGT6
 - Gyro: ICM40605/ICM20608
 - BEC output: 5V 2.5A for autopilot and peripheral hardware
 - BEC output: 5V 2.5A for camera and analog video transmission
 - Barometer: DPS310
 - OSD: AT7456E
 - 12 dedicated PWM/Capture inputs on FMU
 - 5 UARTS: (UART1, UART2, UART3, UART4, UART7)
 - 2 I2C ports
 - 1 DroneCAN port
 - 2 Analog inputs of voltage / current for battery monitoring
 - 2 analog video input channels
 - 1 AV input source switcher switching by relay5
 - 4 relays output control
 - 1 Status LED
 - 1 nARMED

## Pinout

![QioTek AdpetF407 Board](../QioTekAdeptF407/adeptf407_pingout "QioTek AdpetF407")

## UART Mapping

The UARTs are marked Rn and Tn in the above pinouts. The Rn pin is the
receive pin for UARTn. The Tn pin is the transmit pin for UARTn.
|Name|Pin|Function|
|:-|:-|:-|
|SERIAL0|OTG1|USB|
|SERIAL1|TX6/RX6|UART1 (Telem1)|
|SERIAL2|TX3/RX3|UART2 (Telem2 buadrate 921600)|
|SERIAL3|TX1/RX1|UART3 (GNSS)|
|SERIAL4|TX4/RX4|UART4 (Reserve for GNSS2)|
|SERIAL5|TX2/RX2|UART5 (Debug)|

## RC Input
RC input is configured on the RCIN pin by PA15 TIM2_CH1 TIM2 , at one end of the servo rail, marked RC in the above diagram. This pin supports PPM and S.Bus. protocols.

## OSD Support

QioTek AdpetF407 supports OSD using OSD_TYPE 1 (MAX7456 driver).

## PWM Output

The QioTek AdpetF407 AIO supports up to 12 PWM outputs. All 14 PWM outputs have GND on the top row, 5V on the middle row and signal on the bottom row.

The 12 PWM outputs are in 3 groups:

PWM 1 and 4 in group1
PWM 4 and 8 in group2
PWM 9 and 12 in group3

Channels within the same group need to use the same output rate. If any channel in a group uses DShot or  then all channels in the group need to use DShot.

## Battery Monitoring

The board has two dedicated power monitor ports on 6 pin connectors. The correct battery setting parameters are dependent on the type of power brick which is connected.

The correct battery setting parameters are:

BATT_VOLT_PIN 2
BATT_CURR_PIN 3
BATT_VOLT_MULT 20.000
BATT_AMP_PERVLT 17.000
BATT2_VOLT_PIN 14
BATT2_CURR_PIN 15
BATT2_VOLT_MULT 20.000
BATT2_AMP_PERVLT 17.000

In addition, the builtin voltage divider circuit can be used by Solder pad to switching to share the battery voltage monitoring by power2 support to 6S.

## Compass

The QioTek AdpetF407 has a builtin QMC5883 compass. Due to potential interference the board is usually used with an external I2C compass as part of a GPS/Compass combination.

## Loading Firmware

Initial firmware load can be done with DFU by plugging in USB with the
bootloader button pressed. Then you should load the "with_bl.hex"
firmware, using your favourite DFU loading tool.

Once the initial firmware is loaded you can update the firmware using
any ArduPilot ground station software. Updates should be done with the
*.apj firmware files.
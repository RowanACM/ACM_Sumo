/* Turnsensor.h and TurnSensor.cpp provide functions for
configuring the L3GD20H gyro, calibrating it, and using it to
measure how much the robot has turned about its Z axis. */

#pragma once

#include <Zumo32U4.h>
class TurnSensor
{
  public:
    TurnSensor();
    // This constant represents a turn of 45 degrees.
    const int32_t turnAngle45 = 0x20000000;
    
    // This constant represents a turn of 90 degrees.
    const int32_t turnAngle90 = turnAngle45 * 2;
    
    // This constant represents a turn of approximately 1 degree.
    const int32_t turnAngle1 = (turnAngle45 + 22) / 45;
    
    // These are defined in TurnSensor.cpp:
    void turnSensorSetup();
    void turnSensorReset();
    void turnSensorUpdate();
    void calculate360degreeheading();
    uint32_t turnAngle;
    int16_t turnRate;
    int16_t gyroOffset;
    uint32_t readableHeading;
    uint32_t heading360;
    uint16_t gyroLastUpdate;
    
    // These objects must be defined in your sketch.
    Zumo32U4ButtonA buttonA;
    Zumo32U4LCD lcd;
    L3G gyro;
};

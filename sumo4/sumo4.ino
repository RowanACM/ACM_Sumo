#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"
#include "Robot.h"
#define State Robot::State

Zumo32U4ProximitySensors proxSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA button;
Zumo32U4LineSensors lineSensors;
Zumo32U4LCD lcd;
L3G gyro;
Robot robot;

void setup() {
  robot.init();
  robot.calibrateLineSensors(); 
}

void loop() {
  robot.update();
  robot.checkLine();
  switch(robot.state){
    case State::init:
      robot.init();
      break;
    case Robot::State::initMove:
      robot.initMove();
      break;
    case Robot::State::turnDeg:
      robot.turnDeg();
      break;
    case Robot::State::wait:
      robot.wait();
      break;
    case State::atLine:
      robot.atLine();
      break;
    case State::search:
      robot.search();
      break;
    case State::attack:
      robot.attack();
      break;
  }
}

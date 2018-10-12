#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"
#include "Timer.h"
class Robot{
    int lineReadings[3];
    int leftReading;
    int rightReading;
    const int MAX_SPEED = 400;
  public:
    enum class State {init, wait, search, attack, evade, atLine};
    State state = State::init;
    Zumo32U4ProximitySensors proxSensors;
    Zumo32U4Motors motors;
    Zumo32U4ButtonA buttonA;
    Zumo32U4ButtonB buttonB;
    Zumo32U4LineSensors lineSensors;
    Zumo32U4LCD lcd;

    Timer waitTimer;
    Timer turnTimer;

    
    void update(){
      lineSensors.readCalibrated(lineReadings);
      proxSensors.read();
      leftReading = proxSensors.countsFrontWithLeftLeds();
      rightReading = proxSensors.countsFrontWithRightLeds();
    }
    void init(){
      proxSensors.initThreeSensors();
      lineSensors.initThreeSensors();
      Serial.begin(9600);
      //turnSensorSetup();
      //Serial.print("Setup Complete - Waiting for Button");
      ledRed(1);
      state = State::wait;
    }
    void calibrateLineSensors(){
      ledYellow(1);
      lcd.clear();
      lcd.print(F("Black"));
      buttonB.waitForButton();
      for(uint16_t i = 0; i < 50; i++){
        lcd.gotoXY(0,1);
        lcd.print(i);
        lineSensors.calibrate();
      }
      lcd.clear();
      lcd.print(F("White"));
      buttonB.waitForButton();
      for(uint16_t i = 0; i < 50; i++){
        lcd.gotoXY(0,1);
        lcd.print(i);
        lineSensors.calibrate();
      }
      lcd.clear();
      lcd.print(*lineSensors.calibratedMinimumOn);
      lcd.gotoXY(0,1);
      lcd.print(*lineSensors.calibratedMaximumOn);
      buttonB.waitForButton();
      lcd.clear();
    }
    void wait(){
      if(!waitTimer.isSet && buttonA.isPressed()){
        ledRed(0);
        ledYellow(1);
        waitTimer.startTimer();
      }
      if(waitTimer.timeElapsed() < 5000){ //will return 0 if not set
        //lcd.clear();
        lcd.print(5000 - waitTimer.timeElapsed());
        lcd.gotoXY(0,0);
      }
      if(waitTimer.timeElapsed() > 5000){
        waitTimer.reset();
        state = State::search;
        ledYellow(0);
        ledGreen(1);
        lcd.clear();
      }
    }
    void checkLine(){
      if(lineReadings[0] < 50 || lineReadings[1] < 50 || lineReadings[2] < 50){
        if(state != State::init && state != State::wait){
          turnTimer.reset();
          state = State::atLine;
        }
      }
    }
    void turn180deg(){
      turnTimer.startTimerC();
      if(turnTimer.timeElapsed() < 100){
        motors.setSpeeds(-400,-400);
      }
      if(turnTimer.timeElapsed() >= 100 && turnTimer.timeElapsed() < 300){
        motors.setSpeeds(-300,300);
      }
      else if(turnTimer.timeElapsed() >= 300 && turnTimer.timeElapsed() < 500){
        motors.setSpeeds(300,300);
      }
      else{
        turnTimer.reset();
        state = State::search;
      }
    }
    void search(){
      motors.setSpeeds(100,300);
      if(leftReading > 2 || rightReading > 2){
         state = State::attack;
      }
    }
    void attack(){
      //While attacking account for opponent robot movement to adjust to directly hit the opponent.
      int deriv = 50; //to adjust intensity of motors offset for a turn
      //Maybe we should use raw proximity sensor values if we can?
      //Maybe we don't even need to use shitty prox sensors since the kit competition has already passed?
      leftReading = proxSensors.countsFrontWithLeftLeds();
      rightReading = proxSensors.countsFrontWithRightLeds();
      if(leftReading < rightReading)
      {
        int rightMotorSpeed = (((leftReading - rightReading)*deriv) + MAX_SPEED);
        motors.setSpeeds(MAX_SPEED , rightMotorSpeed);
      }
      else if(leftReading > rightReading)
      {
        int leftMotorSpeed = (((rightReading - leftReading)*deriv) + MAX_SPEED);
        motors.setSpeeds(leftMotorSpeed , MAX_SPEED);
      }
      else if(leftReading == rightReading)
      {
        motors.setSpeeds(MAX_SPEED , MAX_SPEED);
      }
    }
    void displayProx(){
      Serial.print(String(leftReading)+ "  " + String(rightReading) + "\n");
    }
};

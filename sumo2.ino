#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"
#include "Timer.cpp"

Zumo32U4ProximitySensors proxSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA button;
Zumo32U4LineSensors lineSensors;
Zumo32U4LCD lcd;
Zumo32U4Encoders encoders;
Zumo32U4Buzzer buzzer;
L3G gyro;

int prox;
String displayString;
int leftReading;
int rightReading;
int lineReadings[3];

typedef enum {Init, Standby, Gambit, Search, Attack, Evasion, Back_off, Reverse}state;
state currentState;

Timer standbyTimer;
Timer gambitTimer;
Timer backOffTimer;
Timer reverseTimer;

int lastRightVal;
int lastLeftVal;

int ogTurn;
void setup() {
  // put your setup code here, to run once:
    proxSensors.initThreeSensors();
    lineSensors.initThreeSensors();
    //Serial.begin(9600);
    currentState = Init;
    turnSensorSetup();

}

void loop() {
  // put your main code here, to run repeatedly:
  switch(currentState){
      case Init:
          //idk why you would have to have anything here but do it anyway
          motors.setSpeeds(0,0);
          currentState = Standby;
          lcd.print("Standby");
          break;
      case Standby:
          if(button.isPressed()){
              standbyTimer.startTimer();
              lcd.print("PAUL");
          }
          if(standbyTimer.timeElapsed() > 5000){
              currentState = Gambit;
              standbyTimer.reset();
          }else if(standbyTimer.isSet){
              lcd.print(5000-standbyTimer.timeElapsed());
          }
          
         break;
     case Gambit:
         gambitTimer.startTimerC();
         switch(gambitTimer.getStage()){
         case 0:
            turnSensorReset();
            gambitTimer.nextStage();
            ogTurn = (((int32_t)turnAngle >> 16) * 360) >> 16;
         case 1:
         //45 degrees is 37 for....some fucking reason
         //180 is 75
            turnSensorUpdate();
            if(((((int32_t)turnAngle >> 16) * 360) >> 16) - ogTurn > 30){
              gambitTimer.nextStage();
            }
            motors.setSpeeds(-200,200);
            lcd.print(((((int32_t)turnAngle >> 16) * 360) >> 16) - ogTurn);
            break;
         case 2:
            lcd.print("Gambit");
            if(gambitTimer.timeElapsed() < 500){
               motors.setSpeeds(400,400);
               break;
            }
            else{
              gambitTimer.nextStage();
              gambitTimer.reset();
            }
         case 3:
            motors.setSpeeds(0,0);
            lcd.print("done");
            currentState = Search;
         }
         break;
    case Search:
      //lcd.clear();
        //this is wrong
//         if(leftReading <= 3 && rightReading <= 3){
 //           currentState = Back_off;
 //           goto cleanup;
 //       }
        motors.setSpeeds(150,-150);
        if(leftReading > 3 && rightReading > 3){
          currentState = Attack;
            }
      delay(100);
        break;
    case Attack:
        //lcd.print("Attack");
        if((encoders.getCountsLeft() - lastLeftVal) < -10  && (encoders.getCountsRight() - lastRightVal) < -10 ){
            currentState = Back_off;
        }
        if(leftReading > rightReading && leftReading > 1){
              motors.setSpeeds(400,200);
        }
        else if(leftReading < rightReading && rightReading > 1){
              motors.setSpeeds(200,400);
        }
        if(leftReading == 0 && rightReading == 0){
            currentState = Search;
        }
        lastLeftVal = encoders.getCountsLeft();
        lastRightVal = encoders.getCountsRight();
        //lcd.print(leftReading + rightReading);
        break;
    case Back_off:
        backOffTimer.startTimerC();
        encoders.getCountsAndResetLeft();
        encoders.getCountsAndResetRight();
        motors.setSpeeds(100,-50);
        if(backOffTimer.timeElapsed() > 5000){
              currentState = Search;
              backOffTimer.reset();
        }
        currentState = Search;
        break;
    case Evasion:
        //turn(180);
        motors.setSpeeds(100,100);
        delay(1000);
        currentState = Search;
        break;
    case Reverse:
        reverseTimer.startTimerC();
        switch(reverseTimer.getStage()){
          case 0:
            //lcd.print("Reverse");
            if(reverseTimer.timeElapsed() < 1000){
               motors.setSpeeds(-100,-100);
               break;
            }
            else{
              reverseTimer.nextStage();
              reverseTimer.reset();
            }
          case 1:
            turnSensorReset();
            reverseTimer.nextStage();
            ogTurn = (((int32_t)turnAngle >> 16) * 360) >> 16;
          case 2:
          //45 degrees is 37 for....some fucking reason
          //180 is 75
            turnSensorUpdate();
            if(((((int32_t)turnAngle >> 16) * 360) >> 16) - ogTurn > 30){
              reverseTimer.nextStage();
            }
            motors.setSpeeds(-200,200);
            //lcd.print(((((int32_t)turnAngle >> 16) * 360) >> 16) - ogTurn);
            break;
         case 3:
            motors.setSpeeds(0,0);
            reverseTimer.nextStage();
            currentState = Search;
        }
        
    }
    //detect side sensors
        //currentState = Evasion;
    //detect line sensors
        //currentState =  Reverse;
  
  proxSensors.read();
  lineSensors.readCalibrated(lineReadings);
  if(lineReadings[0] > 5 || lineReadings[1] > 5 || lineReadings[2] > 5){
    //currentState = Reverse;
  }
  leftReading = proxSensors.countsFrontWithLeftLeds();
  rightReading = proxSensors.countsFrontWithRightLeds();
  //displayString = String(leftReading)+ "  " + String(rightReading);
  //lcd.print(String(currentState));
  //lcd.print((((int32_t)turnAngle >> 16) * 360) >> 16);
  delay(100);
 lcd.clear();
 lcd.print(String(leftReading)+ "  " + String(rightReading));
}





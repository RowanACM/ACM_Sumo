#include <Wire.h>
#include <Zumo32U4.h>
#include "TurnSensor.h"
#include "Timer.h"
class Robot{
    int lineReadings[3];
    int leftReading;
    int rightReading;
    uint32_t turnAngle;
    uint32_t readableHeading;
    uint32_t heading360;
    int16_t turnRate;
    const int32_t turnAngle45 = 0x20000000;
    const int32_t turnAngle180 = turnAngle45*4;
    int16_t gyroOffset;
    uint16_t gyroLastUpdate = 0;
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
    L3G gyro;

    Timer waitTimer;
    Timer turnTimer;

    
    void update(){
      lineSensors.readCalibrated(lineReadings);
      proxSensors.read();
      turnSensorUpdate();
      calculate360degreeheading();
      leftReading = proxSensors.countsFrontWithLeftLeds();
      rightReading = proxSensors.countsFrontWithRightLeds();
      Serial.print(((((int32_t)turnAngle >> 16) * 360) >> 16));
      Serial.print(" ");
      Serial.print(heading360);
      Serial.print(" ");
    }
    void init(){
      proxSensors.initThreeSensors();
      lineSensors.initThreeSensors();
      Serial.begin(9600);
      turnSensorSetup();
      Serial.print("Setup Complete - Waiting for Button");
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
    void calculate360degreeheading()
    {
      if(readableHeading < 0)
      {
        heading360 = 180-readableHeading;
      }
      else
      {
        heading360 = 180+readableHeading;
      }
    }
    void turn180deg(){
      const uint32_t initialHeading = heading360;
      uint32_t toHeading = 0;     
      if(heading360 != toHeading)
      {
        if(initialHeading + 180 > 359)
        {
          toHeading = initialHeading + 180 - 360;
        }
        else
        {
          toHeading = initialHeading + 180;
        }
        turnSensorUpdate();
        motors.setSpeeds(-400,400);
      }
      state = State::search;
      /*turnTimer.startTimerC();
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
      }**/
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
    void turnSensorSetup()
    {
      Wire.begin();
      gyro.init();
    
      // 800 Hz output data rate,
      // low-pass filter cutoff 100 Hz
      gyro.writeReg(L3G::CTRL1, 0b11111111);
    
      // 2000 dps full scale
      gyro.writeReg(L3G::CTRL4, 0b00100000);
    
      // High-pass filter disabled
      gyro.writeReg(L3G::CTRL5, 0b00000000);
    
      lcd.clear();
      lcd.print(F("Gyro cal"));
    
      // Turn on the yellow LED in case the LCD is not available.
      ledYellow(1);
    
      // Delay to give the user time to remove their finger.
      delay(500);
    
      // Calibrate the gyro.
      int32_t total = 0;
      for (uint16_t i = 0; i < 1024; i++)
      {
        // Wait for new data to be available, then read it.
        while(!gyro.readReg(L3G::STATUS_REG) & 0x08);
        gyro.read();
    
        // Add the Z axis reading to the total.
        total += gyro.g.z;
      }
      ledYellow(0);
      gyroOffset = total / 1024;
    
      // Display the angle (in degrees from -180 to 180) until the
      // user presses A.
      lcd.clear();
      turnSensorReset();
      while (!buttonA.getSingleDebouncedRelease())
      {
        turnSensorUpdate();
        lcd.gotoXY(0, 0);
        lcd.print((((int32_t)turnAngle >> 16) * 360) >> 16);
        lcd.print(F("   "));
      }
      lcd.clear();
    }
    void turnSensorReset()
    {
      gyroLastUpdate = micros();
      turnAngle = 0;
    }
    void turnSensorUpdate()
    {
      // Read the measurements from the gyro.
      gyro.read();
      turnRate = gyro.g.z - gyroOffset;
    
      // Figure out how much time has passed since the last update (dt)
      uint16_t m = micros();
      uint16_t dt = m - gyroLastUpdate;
      gyroLastUpdate = m;
    
      // Multiply dt by turnRate in order to get an estimation of how
      // much the robot has turned since the last update.
      // (angular change = angular velocity * time)
      int32_t d = (int32_t)turnRate * dt;
    
      // The units of d are gyro digits times microseconds.  We need
      // to convert those to the units of turnAngle, where 2^29 units
      // represents 45 degrees.  The conversion from gyro digits to
      // degrees per second (dps) is determined by the sensitivity of
      // the gyro: 0.07 degrees per second per digit.
      //
      // (0.07 dps/digit) * (1/1000000 s/us) * (2^29/45 unit/degree)
      // = 14680064/17578125 unit/(digit*us)
      turnAngle += (int64_t)d * 14680064 / 17578125;
      readableHeading = (((int32_t)turnAngle >> 16) * 360) >> 16;
      calculate360degreeheading();
    }
};

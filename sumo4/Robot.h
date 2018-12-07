#pragma once

#include <Wire.h>
#include "Timer.h"
#include <Zumo32U4.h>

class Robot{
    int lineReadings[5];
    int leftReading;
    int rightReading;
    const int MAX_SPEED = 400;
    boolean firstAtLineFlag;
    Timer atLineTimer;
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
    TurnSensor turnSen;

    
    void update();
    void init();
    void calibrateLineSensors();
    void wait();
    void checkLine();
    void atLineFinish(State s);
    void atLine();
    void turnDeg(uint32_t turn);
    void gambit();
    void search();
    void attack();
    void displayProx();
};

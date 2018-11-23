#pragma once
class Timer{
  public:
    Timer();
    boolean isSet;
    int startTime;
    void startTimerC();
    void startTimer();
    int timeElapsed();
    void reset();
};


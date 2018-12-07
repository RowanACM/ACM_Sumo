#include <Zumo32U4.h>
#include "Timer.h"

Timer::Timer(){
  startTime = millis();
  isSet = false;
}
void Timer::startTimerC(){
  if(!isSet){
    startTimer();
  }
}
void Timer::startTimer(){
  startTime = millis();
  isSet = true;
}
int Timer::timeElapsed(){
  if(!isSet)
    return 0;
  return millis() - startTime;
}
void Timer::reset(){
  isSet = false;
}



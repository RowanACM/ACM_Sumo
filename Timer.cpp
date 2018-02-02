#include <Zumo32U4.h>
//this code is so bad---NEVER DO THIS IRL PLS!! -CS
class Timer{
  int startTime = millis();
  int stage = 0;
  public:
    boolean isSet = false;
    void startTimerC(){
      if(!isSet){
        startTimer();
      }
    }
    void startTimer(){
      startTime = millis();
      isSet = true;
    }
    int timeElapsed(){
      if(!isSet)
        return 0;
      return millis() - startTime;
    }
    void reset(){
      isSet = false;
    }
    void setStage(int stage){
      this->stage = stage;
    }
    int getStage(){
      return stage;
    }
    void nextStage(){
      stage++;
    }
};


#include "Declarations.h"
#include "Pins.h"

Timer::Timer(){
  start = millis();
}

unsigned long Timer::time(){
  return millis() - start;
}

void Timer::reset(){
  start = millis();
}

Task::Task(){
}

Task::Task(unsigned long duration, void (*exec)){
  time = new Timer();
  this->duration = duration;
  this->exec = exec;
  doneState = false;
}

bool Task::done(){
	return doneState;
}

void Task::update(){
  exec();
  if (time->time() > duration){
    exec = [](){};
    doneState = true;
  }
}

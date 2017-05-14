#include "Declarations.h"

int taskID;
Task* task;
preTask* taskList;

void initAI(){
  taskList = new preTask[3]{
    straight(150, 10),
    straight(255, 20),
    arc(255, 0, 0.25, ARC_RIGHT)
  };
  taskID = 0;
  task = new Task(taskList[taskID].duration, taskList[taskID].exec);
}

void process(){
	task->update();
 if (task->done()){
  	taskID++;
  	task = new Task(taskList[taskID].duration, taskList[taskID].exec);
 }
}

#ifndef STRUCTS_H
#define STRUCTS_H

struct preTask{
	unsigned long duration;
	void (*exec)();
};

class Timer{
public:

  unsigned long start;

  Timer();
  
  unsigned long time();

  void reset();
};

class Task{
public:
  Task();
  Task(unsigned long, void*);
  void update();
  bool done();
  
private:
  Timer* time;
  unsigned long duration;
  void (*exec)();
  bool doneState;

};

#endif

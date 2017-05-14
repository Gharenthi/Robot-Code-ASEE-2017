#include "Declarations.h"
#include "Pins.h"

volatile int* lightData;
volatile int* proxData;

volatile int lambda_straight_speed;
volatile int lambda_arc_speed;
volatile float lambda_arc_angle;
volatile float lambda_arc_radius;

Timer* proxTimer;

void initInterface(){
  lightData = malloc(sizeof(int)*5);
  proxData = malloc(sizeof(int)*2);

  proxTimer = new Timer();
}

void readData(){
  readLightData();
  if (proxTimer->time() > PROXIMITY_UPDATE_INTERVAL){
    proxTimer->reset();
    readProxData();
  }
}

void readProxData(){
  proxData[0] = readProx(U1_T, U1_E);
  proxData[1] = readProx(U2_T, U2_E);
}

//0=left, 4=right
void readLightData(){
  lightData[0] = analogRead(L1);
  lightData[1] = analogRead(L2);
  lightData[2] = analogRead(L3);
  lightData[3] = analogRead(L4);
  lightData[4] = analogRead(L5);
}

int readProx(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH)*0.034/2;
}

//Exterior wheel speed, turn radius in cm, turn direction
void arcBase(int speed, float radius, int direction){
  digitalWrite(MOV_R, HIGH);
  digitalWrite(REV_R, LOW);
  digitalWrite(MOV_L, HIGH);
  digitalWrite(REV_L, LOW);

  int inner, l, r;
  inner = (speed * radius)/(radius + WHEEL_SPACING);

  if (direction == -1){
    l = speed;
    r = inner;
  }
  else{
    r = speed;
    l = inner;
  }

  analogWrite(ENA_L, l);
  analogWrite(ENA_R, r);
}

//Angle is in tau-radians (1 = full circle)
preTask arc(int speed, float radius, float angle, int direction){
  
  preTask out = {
    (radius + WHEEL_SPACING)*6.28/(speed * SPEED_CONVERSION),
    //[speed, radius, direction](){arcBase(speed, radius, direction);}
    [](){}
  };
  return out;
}

void straightBase(int speed){
  digitalWrite(MOV_R, HIGH);
  digitalWrite(REV_R, LOW);
  digitalWrite(MOV_L, HIGH);
  digitalWrite(REV_L, LOW);

  analogWrite(ENA_L, speed);
  analogWrite(ENA_R, speed);
}

//Distance in units used by Constants::SPEED_CONVERION
preTask straight(int speed, float distance){
  lambda_straight_speed = speed;
  preTask out = {
    distance/(speed * SPEED_CONVERSION),
    []{straightBase(lambda_straight_speed);}
  };
  return out;
}

/*
//angle in range(-1,1), positive = right, negative = left
void move(int speed, float angle){
  digitalWrite(MOV_R, HIGH);
  digitalWrite(REV_R, LOW);
  digitalWrite(MOV_L, HIGH);
  digitalWrite(REV_L, LOW);

  if (angle == 0){
    analogWrite(ENA_R, speed);
    analogWrite(ENA_L, speed);
  }

  if (angle > 0){
    analogWrite(ENA_R, speed);
    analogWrite(ENA_L, 0);
  }

  if (angle < 0){
    analogWrite(ENA_R, 0);
    analogWrite(ENA_L, speed);
  }


  
  int r = speed * logistic(angle);
  int l = speed * logistic(-angle);
  if (r < speed/4) r = 0;
  if (l < speed/4) l = 0;
  if (r > 255) r = 255;
  if (l > 255) l = 255;
  

  analogWrite(ENA_R, r);
  digitalWrite(MOV_R, HIGH);
  digitalWrite(REV_R, LOW);
  

  analogWrite(ENA_L, l);
  digitalWrite(MOV_L, HIGH);
  digitalWrite(REV_L, LOW);
  
}
*/

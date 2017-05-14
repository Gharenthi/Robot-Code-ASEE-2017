#include "Declarations.h"
#include "Pins.h"

void setup() {
  Serial.begin(9600);
  
  pinMode(REV_L,OUTPUT);
  pinMode(MOV_L,OUTPUT);
  pinMode(ENA_L,OUTPUT);

  pinMode(REV_R,OUTPUT);
  pinMode(MOV_R,OUTPUT);
  pinMode(ENA_R,OUTPUT);

  pinMode(U1_T, OUTPUT);
  pinMode(U1_E, INPUT);

  pinMode(U2_T, OUTPUT);
  pinMode(U2_E, INPUT);

  initInterface();
  initAI();
}

void loop() {
  readData();
  process();
}

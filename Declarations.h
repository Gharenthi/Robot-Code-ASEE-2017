#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "Constants.h"
#include "Structs.h"

void initAI();
void process();

void initInterface();
void readLightData();
void readProxData();
void readData();
void move(int, float);
preTask straight(int, float);
preTask arc(int, float, float, int);

#endif

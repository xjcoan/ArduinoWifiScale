/*
  LED Debugging. We might not need this in the final build -
  unless we want to incorporate the internal LED
*/

#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H
#include <Arduino.h>

void powerOffLight(int pin);
void powerOnLight(int pin);

#endif

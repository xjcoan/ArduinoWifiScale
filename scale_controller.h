#ifndef SCALE_CONTROLLER_H
#define SCALE_CONTROLLER_H
#include <Arduino.h>
#include "HX711.h"

long readScale(HX711 scale);

int weighCarafe(HX711 scale);

int checkBoundaries(long reading);

#endif

#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H
#include <Arduino.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

// DEBUG methods to report wifi status to serial
void printWifiData();
void printCurrentNet();

// Currently connects to a singular client
int postCarafePercentage(int weightPercentage);
int checkHealth();

#endif

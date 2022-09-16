#include "led_controller.h"

void powerOnLight(int pin) {
  digitalWrite(pin, HIGH);
}

void powerOffLight(int pin) {
  digitalWrite(pin, LOW);
}

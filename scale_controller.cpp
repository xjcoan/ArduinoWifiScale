#include "scale_controller.h"
#include "math.h"

// Example values
long baseReading = 671500;
long emptyReading = 1658300;
long fullReading = 2658500;

int previousAverage = 0;

long readScale(HX711 scale) {
  Serial.println("Reading scale");
  long reading = abs(scale.read());
  Serial.println((String)"HX711 reading: " + reading);
  return reading;
}

int weighCarafe(HX711 scale) {
  long reading1 = readScale(scale);
  delay(1000);
  long reading2 = readScale(scale);
  delay(1000);
  long reading3 = readScale(scale);

  long avgReading = (reading1 + reading2 + reading3)/3;

  Serial.println((String)"Scale percentage: " + avgReading);

  return checkBoundaries(avgReading);
}

int checkBoundaries(long scaleAverage) {
  if (scaleAverage >= baseReading && scaleAverage <= (emptyReading + 100)) {
    // D'Oh! Carafe's Empty!
    Serial.println("Carafe is empty!");
    return 0;
  } else if (scaleAverage > fullReading) {
    // Pouring it out
    Serial.println("Pouring!");
    return previousAverage;
  } else if (scaleAverage < emptyReading) {
    // Coffee pot's missing!
    Serial.println("Carafe is missing!");
    return -1;
  }

  double calcAvg = (double)scaleAverage / (double)fullReading;
  Serial.println((String)"Computed average: " + calcAvg);

  int percentage = calcAvg * 100;
  if (percentage > 100) {
    percentage = 100;
  }

  if (percentage > previousAverage) {
    Serial.println("reassigning the previous average");
    previousAverage = percentage;
  }
  
  return percentage;
}

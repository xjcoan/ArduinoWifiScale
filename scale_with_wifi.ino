/*

 Based on example code by for WiFiNINA and HX711 libraries
*/

#include "secrets.h"
#include "led_controller.h"
#include "scale_controller.h"
#include "wifi_controller.h"

// Enter values in secrets.h
char ssid[] = WIFI_SSID;      // your network SSID (name)
char pass[] = WIFI_PASSWORD;  // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;  // the WiFi radio's status

// Debug LED pins
const int GREEN_LED = 13;
const int RED_LED = 8;

// HX711 Pins
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

// Instrumentation & Connectivity
HX711 scale;

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  cycleLighting();

  Serial.println("Initializing WIFI");

  // Wifi module error
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    wifiErrorInternalLight();

    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(5000);
  }

  // Wifi connected
  Serial.print("Wifi Connection Successful");
  printWifiData();

  // Intialize scale
  Serial.println("Initializing Scale");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}


void scaleErrorInternalLight() {
  for (int i = 0; i < 6; i++) {
    flashInternalLighting();
  }
}

void wifiErrorInternalLight() {
  for (int i = 0; i < 5; i++) {
    flashInternalLighting();
  }
}

void successfulPostInternalLight() {
  for (int i = 0; i < 2; i++) {
    flashInternalLighting();
  }
}

void unsuccessfulPostInternalLight() {
  for(int i = 0; i < 3; i++) {
    flashInternalLighting();
  }
}

void flashInternalLighting() {
  powerOnLight(LED_BUILTIN);
  delay(1000);
  powerOffLight(LED_BUILTIN);
}

void cycleLighting() {
  Serial.println("Init lights");
  powerOnLight(GREEN_LED);
  powerOnLight(RED_LED);
  delay(1000);

  powerOffLight(GREEN_LED);
  powerOffLight(RED_LED);
}

void sendReading(int reading) {

    int responseStatus = postCarafePercentage(reading);

    if ((String)responseStatus == "200") {
      Serial.println("Successful POST request!");
      successfulPostInternalLight();
    } else {
      Serial.println("Unsuccessful POST request!");
        unsuccessfulPostInternalLight();
    }

}

void loop() {
  delay(30000);
  if (scale.is_ready() && status == WL_CONNECTED) {
    printCurrentNet();

    int reading = weighCarafe(scale);
    sendReading(reading);

  } else if(scale.is_ready() && status != WL_CONNECTED) {
    Serial.println("WIFI module error");
      wifiErrorInternalLight();
  } else {
    Serial.println("Error connecting scale");
      scaleErrorInternalLight();
  }
}

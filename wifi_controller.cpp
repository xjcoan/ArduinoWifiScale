#include "wifi_controller.h"
#include "secrets.h"

char servername[] = SERVER_NAME;
char authUser[] = SERVER_AUTH_USER;
char authPass[] = SERVER_AUTH_PASS;
WiFiSSLClient wifiSSL;
//WiFiClient wifi;
HttpClient client = HttpClient(wifiSSL, servername, 443);


void printWifiData() {
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.println((String)"IP Address: " +  ip);

  printCurrentNet();
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.println((String)"SSID: " + WiFi.SSID());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.println((String)"signal strength (RSSI): " + rssi);
}

int postCarafePercentage(int carafePercentage) {
  Serial.println("making POST request");

  String requestBody = ((String)"{\"level\": " + carafePercentage + "}");

  client.beginRequest();
  client.post("/current_level");
  client.sendHeader("Content-Type", "application/json");
  client.sendHeader("Content-Length", requestBody.length());
  client.sendBasicAuth(authUser, authPass);
  client.beginBody();
  client.print(requestBody);
  client.endRequest();

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  Serial.println("Made POST request!");
  Serial.println((String)"Response code: " + statusCode);
  // We're not using the body currently,  but this is how we access it.
  // String response = client.responseBody();

  return statusCode;
}

int checkHealth() {
  Serial.println("making healthcheck GET request");
  client.get("/health_check");
  client.sendBasicAuth(authUser, authPass);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  // We're not using the body currently,  but this is how we access it.
  //  String response = client.responseBody();

  Serial.println((String)"Health check: " + statusCode);

  return statusCode;
}

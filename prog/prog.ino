
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

void allume() {
  server.send(200, "text/html", "<h1>Right on</h1>");
  digitalWrite(D4, LOW);
}
void eteind() {
  server.send(200, "text/html", "<h1>Right off</h1>");
  digitalWrite(D4, HIGH);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  Serial.println("HTTP server started");
  pinMode(D4, OUTPUT);
  server.on("/", handleRoot);
  server.on("/allume", allume);
  server.on("/eteind", eteind);
  server.begin();
}

void loop() {
  server.handleClient();
}

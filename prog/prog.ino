#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"
#include <SPI.h>
#include <Ethernet.h>

#define PWMA D7
#define AIN1 D1
#define AIN2 D0
#define STBY D3
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
  server.on("/", handleRoot);
  server.on("/startUp", startUp);
  server.on("/shutDown", shutDown);
  server.on("/goForward", goForward);
  server.on("/goBackward", goBackward);
  server.on("/accelerer", accelerer);
  server.on("/ralentir", ralentir);
  server.begin();
}

void loop() {
  server.handleClient();
}
void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

void startUp ()
{
  server.send(200, "text/html", "<h1> ON</h1>");
  Serial.println("Debut");

  digitalWrite(STBY, HIGH);
  Serial.println("STBY");
  delay(1000);
  //ce code est juste pour un test


}

void shutDown ()
{
  server.send(200, "text/html", "<h1>off</h1>");
  digitalWrite(STBY, LOW);
  Serial.println("STBY LOW");
  delay(1000);
}

void goForward ()
{
  if (digitalRead(STBY) == HIGH)
{
  analogWrite(PWMA, 500); //0-1023
  Serial.println("PWMA");
  delay(1000);
  digitalWrite (AIN1, HIGH);
  digitalWrite (AIN2, LOW);
  Serial.println("avancer");
  delay(1000);
}
}

void accelerer ()
{
  if (digitalRead(STBY) == HIGH)
{
  analogWrite(PWMA, 1000); //0-1023
  Serial.println("PWMA");
  delay(1000);
 }
}

void ralentir ()
{
  if (digitalRead(STBY) == HIGH)
{
  analogWrite(PWMA, 500); //0-1023
  Serial.println("PWMA");
  delay(1000);
 }
}


void goBackward ()
{
  if (digitalRead(STBY) == HIGH)
{
  analogWrite(PWMA, 500); //0-1023
  Serial.println("PWMA");
  delay(1000);
  digitalWrite (AIN1, LOW);
  digitalWrite (AIN2, HIGH);
  Serial.println("marche arriere");
  delay(1000);

}
}

void rotateRight (int pwm)
{
  Serial.println("in rotateRight");
  analogWrite(PWMA, 2 * pwm);

}

void rotateLeft (int pwm)
{
  Serial.println("in rotateLeft");
  analogWrite(PWMA, pwm);

}

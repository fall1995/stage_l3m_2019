#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"
#include <SPI.h>
#include <DNSServer.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266mDNS.h>        // Include the mDNS library



/* cablage des broches de la carte de puissance TB6612FNG vers la carte arduino */
#define PWMA D7
#define AIN1 D1
#define AIN2 D0
#define STBY D3
#ifndef APSSID
#define APSSID "iPhone de Aly"
#define APPSK  "af123456789"
#endif
MDNSResponder mdns;
/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;
const byte DNS_PORT = 53;

//IPAddress apIP(172, 20, 10, 6);
//DNSServer dnsServer;

ESP8266WebServer server(80);

void setup()
{
  /*
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  */
  // definition des broches de la carte de puissance en tant que sortie 
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  // Ouvre la voie série avec l'ordinateur
  Serial.begin(115200);
  
  //server.begin();
  //  Connect to Wi-Fi network with SSID and password
  //WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  /*WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Moteur");
  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  // start DNS server for a specific domain name
  dnsServer.start(DNS_PORT, "www.mote.com", apIP);
  */
  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // on affiche l'adresse IP qui nous a ete attribuee
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //-------DNS ne marche pas pour l'instant
  /*
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Moteur");
  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  // start DNS server for a specific domain name

  dnsServer.start(DNS_PORT, "www.mote.com", WiFi.localIP());
  //--------------
    */
  // DNS
   if(!MDNS.begin("esp8266")){             // Start the mDNS responder for esp8266.local
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");
  /*if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS started");
  
  }*/
 
  server.on("/", handleRoot);
  server.on("/startUp", startUp);
  server.on("/shutDown", shutDown);
  server.on("/goForward", goForward);
  server.on("/goBackward", goBackward);
  server.on("/accelerer", accelerer);
  server.on("/ralentir", ralentir);
  
  server.begin();

  // Add service to MDNS-SD
  //MDNS.addService("http", "tcp", 80);
}


void loop()
{
 // dnsServer.processNextRequest();
  server.handleClient();
  
}

void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}



void startUp ()
{
  if (digitalRead(STBY) == LOW)
{
  server.send(200, "text/html", "<h1> ON</h1>");
  Serial.println("Debut");

  digitalWrite(STBY, HIGH);
  Serial.println("STBY HIGH");
  delay(1000);
  digitalWrite (AIN1, LOW);
  digitalWrite (AIN2, LOW);
  //ce code est juste pour un test
} else{
  digitalWrite(STBY, HIGH);
  Serial.println("STBY HIGH");
  delay(1000);
}

}

void shutDown ()
{
  server.send(200, "text/html", "<h1>off</h1>");
  digitalWrite(STBY, LOW);
  Serial.println("STBY LOW");
  digitalWrite (AIN1, LOW);
  digitalWrite (AIN2, LOW);
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
  analogWrite(PWMA, 2000); //0-1023
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

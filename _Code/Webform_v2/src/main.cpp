#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "webapp-index.h"

// SSID & Password
const char *ssid = "ESP32 Access Point"; // Enter your SSID here
const char *password = NULL;             //Can also be a string with a password

// Use this IP adress after connecting to the AP
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

// Handle root url (/)
void handleRoot()
{
  String htmlstring = webappIndex;
  server.send(200, "text/html", htmlstring);
}

void handleQuestion(){
  Serial.println("QUESTION");
}

void handleTest()
{
  Serial.println("TEST");
}

String getURI(String uri){
  int slashPos = uri.indexOf("/__!q");
  String newURI;
  for (int i = slashPos; i < uri.length(); i++)
  {
    newURI.concat(uri.charAt(i));
    Serial.println(newURI);
  }
  return newURI;
}

void setup()
{
  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  // might be you need to set a short delay until
  // the access point is ready for the softAP configuration
  delay(500);

  WiFi.softAPConfig(local_ip, gateway, subnet);

  // set what happens for specific get requests
  server.on("/", handleRoot);
  server.on(getURI(server.uri()),handleQuestion);
  server.on("/testing", handleTest);
  server.uri()

  server.begin();
  Serial.println("HTTP server started");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  delay(100);
}

void loop()
{
  server.handleClient();
}

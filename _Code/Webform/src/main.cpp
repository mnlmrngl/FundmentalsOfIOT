#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include "webapp-index.h"

//**************WEBSERVER**********************
// SSID & Password
const char *ssid = "ESP32 Access Point"; // Enter your SSID here
const char *password = NULL;             //Can also be a string with a password

// Use this IP adress after connecting to the AP
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 1, 1);

WebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

void handleRoot()
{
  String htmlstring = webappIndex;
  server.send(200, "text/html", htmlstring);
}

///*****HTTP CLIENT****************
HTTPClient http;

//*****************WIFI******************
const char *ssid_home = "ESP32 Access Point";
const char *password_home = "";

void handleSave()
{
  Serial.println("Handle Request");
}

//*************WIFI SETUP**********************//
void connectToWiFi()
{
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid_home);

  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid_home, password_home);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//*******************HTTP SETUP************************//
void setupHTTPClient()
{
  // http.begin("http://jsonplaceholder.typicode.com/comments?id=10"); //Specify the URL
  http.begin("192.168.1.1");
  int httpCode = http.GET(); //Make the request
  Serial.println(http.errorToString(httpCode));
  Serial.println(httpCode);
  if (httpCode > 0)
  { //Check for the returning code

    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
  }
  else
  {
    Serial.println("Error on HTTP request");
  }

  http.end(); //Free the resources
}

//*******************WEBSERVER SETUP************************//
void setupWebServer()
{
  WiFi.softAP(ssid, password);

  // might be you need to set a short delay until
  // the access point is ready for the softAP configuration
  delay(500);

  WiFi.softAPConfig(local_ip, gateway, subnet);

  // set what happens for specific get requests
  server.on("/", handleRoot);
  server.on("/save", handleSave);

  server.begin();
  Serial.println("HTTP server started");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  delay(100);
}

//************SETUP*********************//
void setup()
{
  Serial.begin(115200);
  delay(10);
  setupWebServer();
  connectToWiFi();

  setupHTTPClient();
}

void loop()
{
  server.handleClient();
}

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "webapp-index.h"
#include <HTTPClient.h>

// SSID & Password
const char *ssid = "ESP32 Access Point"; // Enter your SSID here
const char *password = NULL;             //Can also be a string with a password

// Use this IP adress after connecting to the AP
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

String serverName = "localhost:80";


void setup()
{
  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  // might be you need to set a short delay until
  // the access point is ready for the softAP configuration
  delay(500);

  WiFi.softAPConfig(local_ip, gateway, subnet);

  server.begin();
  Serial.println("HTTP server started");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  delay(100);
}

void loop()
{
      HTTPClient http;

      String serverPath = serverName + "?temperature=24.37";
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();

      delay(500);
}

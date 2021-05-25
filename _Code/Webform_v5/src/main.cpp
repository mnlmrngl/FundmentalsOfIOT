#include <WiFi.h>
#include "webapp-index.h"
#include <SPIFFS.h>

const char *ssid = "ESP32-Access-Point";
const char *password = NULL;

String htmlstring = webappIndex;

WiFiServer server(80);

// Variable to store the HTTP request
String header;

String getInput(int begin, int end)
{
  String input;

  for (int i = begin + 4; i < end; i++)
  {
    input += header.charAt(i);
  }
  return input;
}

void setupWiFi()
{
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void setup()
{
  Serial.begin(115200);
  setupWiFi();
  setupSPIFFS();
}

void loop()
{
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client)
  {                                // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    // String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {

        // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
                                //        // Serial.write(c);        // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          // if (currentLine.length() == 0)
          // {
          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
          // and a content-type so the client knows what's coming, then a blank line:
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();

          if (header.indexOf("GET /save") >= 0)
          {
            Serial.println("HEADER " + header);

            int indexQ = header.indexOf("__!q");
            int indexA = header.indexOf("__!a");
            int indexB = header.indexOf("__!b");
            int indexC = header.indexOf("__!c");
            int indexD = header.indexOf("__!d");

            Serial.println(indexA - indexQ);

            Serial.println("Frage: " + getInput(indexQ, indexA));
            Serial.println("Antwort A: " + getInput(indexQ, indexA));
            Serial.println("Antwort B: " + getInput(indexA, indexB));
            Serial.println("Antwort C: " + getInput(indexB, indexC));
            Serial.println("Antwort D: " + getInput(indexC, indexD));
          }
          else if (header.indexOf("GET /getQuestions") >= 0)
          {
            File fileToRead = SPIFFS.open("/test.txt");

            if (!fileToRead)
            {
              Serial.println("Failed to open file for reading");
              return;
            }

            Serial.println("File Content:");

            while (fileToRead.available())
            {

              Serial.write(fileToRead.read());
            }

            fileToRead.close();
          }
          else
            client.println(webappIndex);
          break;
        }
      }
    }

    header = "";
    // Close the connection
    client.stop();
  }
}

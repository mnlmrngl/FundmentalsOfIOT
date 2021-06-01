#include <WiFi.h>
#include <webapp-index.h>
#include <SPIFFS.h>

// Replace with your network credentials
const char *ssid = "ESP32-Access-Point";
const char *password = NULL;

String htmlstring = webappIndex;

WiFiClient client;

// Set web server port number to 80
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
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void setupSPIFFS()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    ESP.restart();
  }
}

void setup()
{
  Serial.begin(115200);
  setupSPIFFS();
  setupWiFi();
}

void loop()
{
  client = server.available(); // Listen for incoming clients

  if (client)
  {                                // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();

          // turns the GPIOs on and off
          if (header.indexOf("GET /save") >= 0)
          {
            File questionFile = SPIFFS.open("/newQuestions.txt", FILE_APPEND);

            int indexQ = header.indexOf("__!q");
            int indexA = header.indexOf("__!a");
            int indexB = header.indexOf("__!b");
            int indexC = header.indexOf("__!c");
            int indexD = header.indexOf("__!d");

            questionFile.println("F: " + getInput(indexQ, indexA));
            questionFile.println("A: " + getInput(indexA, indexB));
            questionFile.println("B: " + getInput(indexB, indexC));
            questionFile.println("C: " + getInput(indexC, indexD));
            questionFile.println("D: " + getInput(indexD, header.length() - 11));
            questionFile.println();

            questionFile.close();
          }
          else if (header.indexOf("GET /download") >= 0)
          {
            File questionFile = SPIFFS.open("/newQuestions.txt");


            Serial.println("File Content:");

            String downloadContent;

            while (questionFile.available())
            {
              downloadContent += char(questionFile.read());
              // Serial.write(questionFile.read());
            }
            questionFile.close();

            Serial.println(downloadContent);
          }
          // Display the HTML web page
          client.println(htmlstring);
          break;
        }
        else
        { // if you got a newline, then clear currentLine
          currentLine = "";
        }
      }
    }
    // Clear the header variable
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
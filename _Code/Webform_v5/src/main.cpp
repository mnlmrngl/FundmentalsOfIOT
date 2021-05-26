#include <WiFi.h>
#include <webapp-index.h>

// Replace with your network credentials
const char *ssid = "ESP32-Access-Point";
const char *password = NULL;

String htmlstring = webappIndex;

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

void setup()
{
  Serial.begin(115200);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void loop()
{
  WiFiClient client = server.available(); // Listen for incoming clients

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

          Serial.println("HEADER " + header);

          // turns the GPIOs on and off
          if (header.indexOf("GET /save") >= 0)
          {
            int indexQ = header.indexOf("__!q");
            int indexA = header.indexOf("__!a");
            int indexB = header.indexOf("__!b");
            int indexC = header.indexOf("__!c");
            int indexD = header.indexOf("__!d");

            Serial.println(indexA - indexQ);

            Serial.println("Frage: " + getInput(indexQ, indexA));
            Serial.println("Antwort A: " + getInput(indexA, indexB));
            Serial.println("Antwort B: " + getInput(indexB, indexC));
            Serial.println("Antwort C: " + getInput(indexC, indexD));
            Serial.println("Antwort D: " + getInput(indexD, header.length()-11));
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
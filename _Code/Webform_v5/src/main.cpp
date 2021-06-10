#include <WiFi.h>
#include <SPIFFS.h>
// #include <webapp-download.h>
#include "webapp-start.h"

// Replace with your network credentials
const char *ssid = "ESP32-Access-Point";
const char *password = NULL;

String htmlstring = webappStart;

WiFiClient client;

bool download = false;

String downloadContent;

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

String getFirst(String url, String toReplace)
{
  return url.substring(0, url.indexOf(toReplace));
}

String getLast(String url, String toReplace)
{
  return url.substring(url.indexOf(toReplace) + toReplace.length(), url.length());
}

String encodeOneChar(String url, String toReplace, String newStr)
{
  return getFirst(url, toReplace) + newStr + getLast(url, toReplace);
}

String encodeOneCharType(String str, String toReplace, String newStr)
{
  while (str.indexOf(toReplace) >= 0)
  {
    str = encodeOneChar(str, toReplace, newStr);
  }
  return str;
}

String encodeFullString(String str)
{
  str = encodeOneCharType(str, "%C3%9F", "ß");
  str = encodeOneCharType(str, "%C3%A4", "Ä");
  str = encodeOneCharType(str, "%C3%84", "ä");
  str = encodeOneCharType(str, "%C3%B6", "Ö");
  str = encodeOneCharType(str, "%C3%96", "ö");
  str = encodeOneCharType(str, "%C3%BC", "Ü");
  str = encodeOneCharType(str, "%C3%9C", "ü");
  str = encodeOneCharType(str, "%20", " ");
  str = encodeOneCharType(str, "%21", "!");
  str = encodeOneCharType(str, "%22", "\"");
  str = encodeOneCharType(str, "%23", "#");
  str = encodeOneCharType(str, "%24", "$");
  str = encodeOneCharType(str, "%25", "%");
  str = encodeOneCharType(str, "%26", "&");
  str = encodeOneCharType(str, "%27", "'");
  str = encodeOneCharType(str, "%28", "(");
  str = encodeOneCharType(str, "%29", ")");
  str = encodeOneCharType(str, "%2A", "*");
  str = encodeOneCharType(str, "%2B", "+");
  str = encodeOneCharType(str, "%2C", ",");
  str = encodeOneCharType(str, "%2D", "-");
  str = encodeOneCharType(str, "%2E", ".");
  str = encodeOneCharType(str, "%2F", "/");
  str = encodeOneCharType(str, "%3A", ":");
  str = encodeOneCharType(str, "%3B", ";");
  str = encodeOneCharType(str, "%3C", "<");
  str = encodeOneCharType(str, "%3D", "=");
  str = encodeOneCharType(str, "%3E", ">");
  str = encodeOneCharType(str, "%3F", "?");
  str = encodeOneCharType(str, "%40", "@");
  str = encodeOneCharType(str, "%5B", "[");
  str = encodeOneCharType(str, "%5D", "]");
  str = encodeOneCharType(str, "%7B", "{");
  str = encodeOneCharType(str, "%7C", "|");
  str = encodeOneCharType(str, "%7D", "}");

  return str;
}

String getInput(int begin, int end)
{
  String input;

  for (int i = begin + 4; i < end; i++)
  {
    input += header.charAt(i);
  }

  input = encodeFullString(input);

  Serial.println(input);
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
          htmlstring = webappStart;
          client.println(htmlstring);

          if (header.indexOf("GET /save") >= 0)
          {
            download = false;
            File questionFile = SPIFFS.open("/newQuestions.txt", FILE_APPEND);

            int indexQ = header.indexOf("__!q");
            int indexA = header.indexOf("__!a");
            int indexB = header.indexOf("__!b");
            int indexC = header.indexOf("__!c");
            int indexD = header.indexOf("__!d");

            questionFile.print("__F: " + getInput(indexQ, indexA) + " __A: " + getInput(indexA, indexB) + "  __B: " + getInput(indexB, indexC) + " __C: " + getInput(indexC, indexD) + " __D: " + getInput(indexD, header.length() - 11));

            questionFile.close();
          }
          else if (header.indexOf("GET /download") >= 0)
          {
            download = true;
            File questionFile = SPIFFS.open("/newQuestions.txt");

            Serial.println("File Content:");

            while (questionFile.available())
            {
              downloadContent += char(questionFile.read());
            }
            questionFile.close();
          }
          else if (header.indexOf("GET /delete") >= 0)
          {
            SPIFFS.remove("/newQuestions.txt");
          }
          if (download)
          {
            Serial.println(downloadContent);

            client.println("<button onclick=\"downloadFile('WanderschildFragen','" + downloadContent + "')\"> Starte DOwnload </button>");
          }

          client.println("</body></html>");
          break;
        }
        else
        {
          currentLine = "";
        }
      }
    }

    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
/**
 * 
 * Over the Air
 * Send Data to an End-Point within via Network
 * 
 * What you need:
 * - Basic software environment (VSC, PlatformIO and Postman for API Testing)
 * - Basic hardware requirements (ESP32, Breadboard, MicroUSB)
 * - Some Wires
 * 
 * 
 * #Part 1: Prepare sensor setup
 * For the sake of simplicity we are going to use a touch sensor input again
 * and read that data. For testing purposes you can output the data again
 * with the serial monitor.
 * 
 * #Part 2: Connect to wifi
 * For the communication to a service we need to connect the ESP to the 
 * network via wifi. I prepared some useful functions in wifi_connection.
 * You need to add your wifi credentials. A smart approach would be if
 * you store these sensitive information in another file (wifi_credentials.h),
 * define your credentials as constants. This filename is excluded in .gitignore,
 * in case if you push this exercise on some git cloud platform.
 * 
 * #Part 3: Prepare end-point
 * The measured data should be piped via the network somewhere and should be
 * displayed. Of course you can code your serverside end-point from skratch,
 * but I would prefer the lazy method for this test. 
 * a) One approach: Use is [ThingSpeak](https://thingspeak.com)
 * you just need to sign-up with your HFU mail (our university has a cooperation).
 * After sign-in you can create a channel with some fields.
 * b) Another approach: Fire your data to your telegram bot.
 * Here is a great introduction how to use the telegram API:
 * [Send and Receive Messages with the Telegram API](https://wk0.medium.com/send-and-receive-messages-with-the-telegram-api-17de9102ab78)
 * 
 * #Part 4: Test end-point
 * Postman is a great and powerful API testing tool. So, copy the GET URL of your
 * ThingSpeak Channel (or the URL of your chat with your bot via Telegram API) and call this URL from Postman (you can manipulate the field data
 * directly in the url get parameters). After firing the call the value should be
 * visible in your dashboard (or should display the information in your telegram messenger).
 * 
 * #Part 5: ESP calls
 * Finally your can hand the API call over to the ESP code. Make sure your ESP is
 * not calling the URL every xx miliseconds, use some delay (e.g. 1 second).
 * 
 * 
*/

#include <Arduino.h>
#include "wifi_connection.h"
#include "thingspeak.h"

const int ledPin = 21;
const int touchInput = 0;
int threshold = 30;

WiFiClient client;
int number = 0;


unsigned long myChannelNumber = 1353572;         // Deine ThingSpeak Kanal Nummer
const char * myWriteAPIKey = "5OSADRN49F5A5318"; // Dein ThingSpeak API Key


void setup() {
  Serial.begin(115200);
  threshold = touchRead(touchInput);
  pinMode(touchInput,INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.println("ESP is on");

  initWifi();

  ThingSpeak.begin(client);
}

void loop() {
  checkWifi();


  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, number, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  // change the value
  number++;
  if(number > 99){
    number = 0;
  }
  
  delay(20000); // Wait 20 seconds to update the channel again
  
  // delay(100);
  // Serial.println(touchRead(touchInput));
  // Serial.println(threshold);
  // if(touchRead(touchInput) < threshold){
  //   digitalWrite(ledPin, HIGH);
  //   Serial.println("ON");
  // }else{
  //   digitalWrite(ledPin, LOW);
  //   Serial.println("OFF");
  // }
  // Serial.println();
}
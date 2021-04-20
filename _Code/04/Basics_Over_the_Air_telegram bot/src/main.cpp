#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Wifi network station credentials
// #define WIFI_SSID "Canon_TS3300series"
// #define WIFI_PASSWORD "Zimtschnecke"
#define WIFI_SSID "Anita"
#define WIFI_PASSWORD "2612199703071988"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "1650685583:AAFag0bpFx4LZJ0INlNYBERgEhXj1fFWvUs"

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

const int ledPin = 21;
int ledStatus = 0;
const int touchInput = 0;
const int touchTreshold = 30;

void handleNewMessages(int numNewMessages){
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++){
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";
if(touchRead(touchInput) < touchTreshold){
    if (text == "/ledon"){
      
        digitalWrite(ledPin, HIGH); // turn the LED on (HIGH is the voltage level)
        Serial.println("PIN "+ledPin);
        ledStatus = 1;
        bot.sendMessage(chat_id, "Led is ON", "");
      
    }

    if (text == "/ledoff"){
      ledStatus = 0;
      digitalWrite(ledPin, LOW); // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led is OFF", "");
    }
    }else{
        bot.sendMessage(chat_id, "Safety Switch is not touched!");
      }

    if (text == "/status"){
      if (ledStatus){
        bot.sendMessage(chat_id, "Led is ON", "");
      }
      else{
        bot.sendMessage(chat_id, "Led is OFF", "");
      }
    }

    if (text == "/start"){
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Flash Led Bot example.\n\n";
      welcome += "/ledon : to switch the Led ON\n";
      welcome += "/ledoff : to switch the Led OFF\n";
      welcome += "/status : Returns current status of LED\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}


void setup(){
  Serial.begin(115200);
  Serial.println();

  pinMode(touchInput, INPUT);

  pinMode(ledPin, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(ledPin, HIGH); // initialize pin as off (active LOW)

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

void loop(){
  if (millis() - bot_lasttime > BOT_MTBS)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }

  Serial.println(touchRead(touchInput));
}
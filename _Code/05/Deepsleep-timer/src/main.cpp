#include <Arduino.h>

#define MICROSECONDS_TO_SECONDS 500000

#define ledPin 18

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(5000);

  Serial.println("Set timer to wake esp up");
  esp_sleep_enable_timer_wakeup(10 * MICROSECONDS_TO_SECONDS); //danach startet setup();
  

  delay(5000);
  Serial.println("Fall asleep");
  esp_deep_sleep_start();
}

void loop() {
  
}
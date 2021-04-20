/**
 * 
 * Hello World Blink
 * 
 * What you need:
 * - Basic software environment (VSC, PlatformIO)
 * - Basic hardware requirements (ESP32, Breadboard, MicroUSB)
 * - LED, Wire
 * 
 * 
 * #Part 1: Use Variables and Serial Monitor
 * Print out some static variables via serial monitor
 * 
 * 
 * #Part 2: Blink LED continuously
 * Connect led to board (e.g. via pin 21). 
 * Note: make sure to connect led's cathode to ground!
 * Make led shine.
 * Then, write some lines of code to blink the led continuously.
 * 
 * 
 * #Part 3: Touch sensor
 * Connect wire to touch pin (e.g. on Touch0 ~ pin 24)
 * Print touch sensor value to serial monitor
 * 
 * 
 * #Part 4: Touch to Blink
 * Write some lines of code to switch led on
 * only if wire is touched
 * 
 *  
*/

#include <Arduino.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(12, HIGH);
  Serial.println("on");
  delay(750);
  digitalWrite(12, LOW);
   Serial.println("off");
  delay(750);
}
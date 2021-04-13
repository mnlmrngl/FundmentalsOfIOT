/**
 * 
 * Selfmadey Makey
 * Capacitive Touch Bananas trigger Processing 
 * and play some sound (the selfmade version of
 * a makey makey board)
 * 
 * What you need:
 * - Basic software environment (VSC, PlatformIO and Processing)
 * - Basic hardware requirements (ESP32, Breadboard, MicroUSB)
 * - Some Wires, some fruits (banana, apple...)
 * 
 * 
 * #Part 1: Touch sensor
 * Connect wire to touch pin (e.g. on Touch0 ~ pin 24)
 * Print touch sensor value to serial monitor.
 * Then stick wire into fruit, observe sensor data to
 * adjust your code: when banana is touched, than the
 * value 1 should be piped to the serial port, else
 * just 0.
 * 
 * 
 * #Part 2: Switch to processing
 * In the subfolder of this exercise you'll find a skeleton
 * of a processing sketch. Read all further details there.
 * The goal is: touching banana should 
 * a) colorize screen in red
 * b) play a sound
 * 
 * 
 * #Part 3: More fruits
 * As soon as one fruit is playing you can continue
 * to exents your fruit keyboard
 *  
*/
#include <Arduino.h>
const int ledPin = 21;
const int touchInput = 0;
const int threshold = 30;
char val;

void setup() {
  Serial.begin(115200);
  
  pinMode(touchInput,INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  delay(100);
  Serial.println(touchRead(touchInput));
  Serial.println(threshold);
  if(touchRead(touchInput) < threshold){
    digitalWrite(ledPin, HIGH);
    Serial.println("ON");
  }else{
    digitalWrite(ledPin, LOW);
    Serial.println("OFF");
  }

  val = Serial.read();
  Serial.println();
}
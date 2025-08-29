/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.
  This code is to test if our connection of LED to ESP8266 (NodeMCU) is working.
*/
//#define LED_PIN D1
#define LED_PIN 2  // for ESP32 WROOM Dev Board (30pin)
// const int LED_PIN = 5;  //alternatively for ESP8266

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

// #include <ESP8266WiFi.h>  //for ESP8266
#include <PubSubClient.h>
#include <WiFi.h>  // for ESP32
// GPIO 5 D1
// GPIO 4 D2
// #define LED_PIN D1
#define LED_PIN 2 // for ESP32 WROOM Dev Board (30pin)

// WiFi
const char *ssid = "SUTD_Guest"; // Enter your WiFi name
const char *password = "";  // Enter WiFi password

// MQTT Broker
//const char *mqtt_broker = "test.mosquitto.org";
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "sutd/group0/led";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
      // connecting to a WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
}

void reconnect() {
    while (!client.connected()) {
        String client_id = "esp8266-client-";
        client_id += String(WiFi.macAddress());
        Serial.println("Connecting to public emqx mqtt broker.....");
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Public emqx mqtt broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    // publish and subscribe
    client.publish(topic, "hello emqx");
    client.subscribe(topic);  
}

void setup() {
    // Set software serial baud to 115200;
    Serial.begin(115200);
    setup_wifi();
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); 
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    String message;
    for (int i = 0; i < length; i++) {
        message = message + (char) payload[i];  // convert *byte to string
    }
    Serial.print(message);
    if (message == "on") { digitalWrite(LED_PIN, HIGH); }   // LED on
    if (message == "off") { digitalWrite(LED_PIN, LOW); } // LED off
 // CH modified for blinking if message "blink" is sent ///
    if (message == "blink") 
      {
        for (int y = 0; y < 5; y++) {
          digitalWrite(LED_PIN, LOW);
          delay(1000);                       // wait for a second;
          digitalWrite(LED_PIN, HIGH);
          delay(1000);                       // wait for a second;
          digitalWrite(LED_PIN, LOW);
          }
      }   // end of blink
    
    Serial.println();
    Serial.println("-----------------------");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
    client.loop();
}

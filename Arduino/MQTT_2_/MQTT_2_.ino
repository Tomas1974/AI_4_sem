#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "passwords.h"  // Your WiFi and MQTT credentials

// Ports on ESP32
const int BUTTON = 26;
const int LED_GREEN = 25;
const int TEMP_SENSOR = 17;

// Variables
int buttonState = 0;
int lastButtonState = 1;
int tempON = LOW;
float tempC; // temperature in Celsius
int satisfaction = 0;
bool start=false;

OneWire oneWire(TEMP_SENSOR);
DallasTemperature DS18B20(&oneWire);

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
    
  
if (start)
  start=false;
  else
  start=true;

 
 
  
}

void setup() {
  Serial.begin(9600);

  // WIFI connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // MQTT connection
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("connected");
      client.setCallback(callback);  // Set the callback function
      client.subscribe("esp/return"); // Subscribe to the topic
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  client.publish("esp/test", "Hello from ESP32");

  // Define pinModes
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED_GREEN, OUTPUT);
  DS18B20.begin();
}

void loop() {
  client.loop();

  
  
  if (start)
  {
    
    digitalWrite(LED_GREEN, HIGH);  // Update the LED
    DS18B20.requestTemperatures();  // Send the command to get temperatures
    tempC = DS18B20.getTempCByIndex(0);  // Read temperature in °C
    char message[20];
    sprintf(message, "%.1f", tempC);
    Serial.println(tempC);
    client.publish("esp/temp", message);
    delay(1000);   
     
    }
    else
  digitalWrite(LED_GREEN, LOW);  // Update the LED
  
  

  
    
  
  
}
#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "passwords.h"  // Your WiFi and MQTT credentials
#include <LiquidCrystal_I2C.h>


// Ports on ESP32
const int BUTTON = 26;
const int LED_GREEN = 25;
const int TEMP_SENSOR = 17;
const int BUTTON_Menu = 16;
const int BUTTON_Choise = 4;

// Variables to temp censor
float tempC; // temperature in Celsius

//Translated from broker to start mesuring
bool start=false;

//Variables to buttons
int buttonState_Menu = 0;
int buttonState_Choise = 0;
int lastButtonState_Menu = 0;
int lastButtonState_Choise = 0;
unsigned long lastUpdateTime = 0; 
int programNumber=0;
int programChoise=0;


//Variables screen
int lcdColumns = 16;
int lcdRows = 2;


//Hardware and connections varibles
OneWire oneWire(TEMP_SENSOR);
DallasTemperature DS18B20(&oneWire);
WiFiClient espClient;
PubSubClient client(espClient);
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  




void callback(char* topic, byte* payload, unsigned int length) {
  
if (start)
  start=false;
  else
  start=true;
  
}

void wifiConnection(String ssid, String password)
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to "+ssid+" WIFI");
  }
  Serial.println("Connected to the WiFi network");

}


void mqttConnection()
{
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
}


void setup() {
  Serial.begin(9600);

  
  lcd.init();
  lcd.backlight();

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUTTON_Menu, INPUT_PULLUP);
  pinMode(BUTTON_Choise, INPUT_PULLUP);
  DS18B20.begin();
}



void button_Menu(long currentTime)
{
    buttonState_Menu = digitalRead(BUTTON_Menu);
    
  if (buttonState_Menu != lastButtonState_Menu) {
    

    if (buttonState_Menu == HIGH) {
      
        programNumber++;
        lastUpdateTime = currentTime;
     
      if (programNumber==3)
      programNumber=1;
      
      
    }

    delay(50); // Debounce delay
  }

  lastButtonState_Menu = buttonState_Menu;

buttonState_Choise = digitalRead(BUTTON_Choise);

}



void button_Choise()
{
if (buttonState_Choise != lastButtonState_Choise) {
    

      
    if (buttonState_Choise == HIGH) {
      
       programChoise=programNumber;
        
    }

    switch(programChoise)
      {
      
      case 1:
      wifiConnection(hjemme_ssid, hjemme_password);
      mqttConnection();
      break;

      case 2:
      wifiConnection(skole_ssid, skole_password);
      mqttConnection();
      break;

      
      }

  }

  lastButtonState_Choise = buttonState_Choise;
}




void loop() {
  client.loop();
   unsigned long currentTime = millis();
 

   
  if (start)
  {

  unsigned long timeWent=currentTime-lastUpdateTime;
  
  if (timeWent>=1000)
  {
  
    DS18B20.requestTemperatures();  // Send the command to get temperatures
    tempC = DS18B20.getTempCByIndex(0);  // Read temperature in °C
    char message[20];
     sprintf(message, "%.1f", tempC);


     lcd.clear();
     lcd.print("Vis temp. "+ String(message));
    
    digitalWrite(LED_GREEN, HIGH);  // Update the LED
    
    client.publish("esp/temp", message);
    }
     
    }
    else
 {

  digitalWrite(LED_GREEN, LOW);  // Update the LED
  
  button_Menu(currentTime);
  button_Choise();


lcd.setCursor(0,1);
switch(programNumber)
      {
      
      case 1:
      lcd.clear();
      lcd.print("Hjemme WIFI");
      
      break;

      case 2:
      lcd.clear();
      lcd.print("Skole WIFI");
      
            
      }

   

  unsigned long timeWent=currentTime-lastUpdateTime;
  if (timeWent>=5000)
  programNumber=programChoise;
  
  delay(50);

 }
 
  
}
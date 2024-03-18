#include <WiFi.h>

#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "passwords.h"  // Your WiFi and MQTT credentials
#include <LiquidCrystal_I2C.h>
#include "WifiMenu.h"
#include "WifiModel.h"





// Ports on ESP32

const int LED_GREEN = 25;
const int TEMP_SENSOR = 17;
const int BUTTON_Menu = 16;
const int BUTTON_Choise = 4;


//Variables screen
int lcdColumns = 16;
int lcdRows = 2;



// Variables to temp censor
float tempC; // temperature in Celsius

//Translated from broker to start mesuring
bool start=false;


bool mqttConnect=false;
long lastUpdateTime;


//Hardware and connections varibles
OneWire oneWire(TEMP_SENSOR);
DallasTemperature DS18B20(&oneWire);
WiFiClient espClient;
PubSubClient client(espClient);

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  


WifiModel wifiNetworks[] = {
  WifiModel(hjemme_name, hjemme_ssid, hjemme_password),
  WifiModel(skole_name, skole_ssid, skole_password),
  WifiModel("ABC", "DEF", "GHI")

};

//WifiMenu wifiMenu(skærm variabel, netværks array, antal objekter i array, knap et input, knap to input);
WifiMenu wifiMenu( lcd, wifiNetworks, 3, BUTTON_Menu, BUTTON_Choise);



void callback(char* topic, byte* payload, unsigned int length) {
  
if (start)
  start=false;
  else
  start=true;
  
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

  wifiMenu.initialize();
    lcd.init();                    
    lcd.backlight();
  
  pinMode(LED_GREEN, OUTPUT);
  DS18B20.begin();
}


void loop() {
  
  client.loop();
  
   long currentTime = millis();
  

   
  if (start)
  {

    long timeWent=currentTime-lastUpdateTime;

  
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
    
    lastUpdateTime=currentTime;
    }
       delay(50);
      

    }
    else
 {

  digitalWrite(LED_GREEN, LOW);  // Update the LED
  
    wifiMenu.wifiMenuSystem();


    if (wifiMenu.getwifiON() !="")
      mqttConnect==false; 

    if (wifiMenu.getwifiON() !="" && mqttConnect==false)
    {
       mqttConnection();
       mqttConnect==true; 
    }
     
  
  delay(50);

 }
 
  
}
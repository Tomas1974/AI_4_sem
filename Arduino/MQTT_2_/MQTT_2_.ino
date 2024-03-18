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



// Variabler til temperatursensor
float tempC; // temperature in Celsius
long lastUpdateTime; //Bruges til tidsmåling til temperaturer


//Starter temperatursensoren, hvis den er sand.
bool start=false;




//Hardware and connections varibles
OneWire oneWire(TEMP_SENSOR);
DallasTemperature DS18B20(&oneWire);

//Pubsub til brokeren
WiFiClient espClient;
PubSubClient client(espClient);

//Skærm
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  


//Objekter med passwords til WifiMenu
WifiModel wifiNetworks[] = {
  WifiModel(hjemme_name, hjemme_ssid, hjemme_password), //Strings fra passwords.h
  WifiModel(skole_name, skole_ssid, skole_password),
    
};

//WifiMenu wifiMenu(skærm variabel, netværks array, antal objekter i array, knap et bladre i menu, knap to vælge i menuen);
WifiMenu wifiMenu( lcd, wifiNetworks, 2, BUTTON_Menu, BUTTON_Choise);


//Broker signal fra c# om at starte temperatursensoren
void callback(char* topic, byte* payload, unsigned int length) {
  
if (start)
  start=false;
  else
  start=true;
  
}



void mqttConnection()
{
   client.setServer(mqttServer, mqttPort);
  while (!client.connected()) //Metoden springes over, hvis der er forbindelse i forvejen.
  {
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
  DS18B20.begin(); //En del af Dallas temperatur beregneren.
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
       
      

    }
    else
 {

  digitalWrite(LED_GREEN, LOW);  // Slukker led, når der ikke er forbindelse
  
    wifiMenu.wifiMenuSystem();

  
    
    if (wifiMenu.getwifiON() !="") //Den skal ikke forbinde, hvis der ikke er internet.
       mqttConnection(); 
    

 }
 delay(50);
  
}
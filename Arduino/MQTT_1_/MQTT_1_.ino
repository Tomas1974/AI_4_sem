#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "passwords.h" 

//Password is placed in passwords.h



/******* Ports on Esp32********/

const int BUTTON = 16;
const int LED_GREEN = 4;
const int TEMP_SENSOR = 17; 


/******* Variables ********/

int buttonState = 0;
int lastButtonState = 1;
int tempON = LOW;
float tempC; // temperature in Celsius


OneWire oneWire(TEMP_SENSOR);
DallasTemperature DS18B20(&oneWire);


WiFiClient espClient;
PubSubClient client(espClient);

int satisfaction = 0;

void setup() {


Serial.begin(9600);

/******* WIFI connection********/

WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
}
 
Serial.println("Connected to the WiFi network");


/******* MQTT connection********/

client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) 
  {
      Serial.println("Connecting to MQTT...");
 
      if (client.connect("ESP32Client", mqttUser, mqttPassword )) 
      Serial.println("connected");
 
     else 
    {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }

  }
  
client.publish("esp/test", "Hello from ESP32");

/******* Define pinModes********/
  
pinMode(BUTTON, INPUT_PULLUP);
pinMode(LED_GREEN, OUTPUT);

DS18B20.begin(); 


}

void loop() {

  client.loop();
 

   buttonState = digitalRead(BUTTON);

  if (buttonState != lastButtonState) // Button state has changed
  {    

    if (buttonState == HIGH) // Button is pressed
    { 
      
      tempON = !tempON; // Toggle the light state

       
      if (tempON == HIGH) 
        Serial.println("Temp ON");
      else 
        Serial.println("Temp OFF");
      

        digitalWrite(LED_GREEN, tempON); // Update the LED
    }
    
  }


  lastButtonState = buttonState;


  if (tempON==HIGH)
  {
  
    
      if (millis() > 1000) 
      {

      DS18B20.requestTemperatures();       // send the command to get temperatures
      tempC = DS18B20.getTempCByIndex(0);  // read temperature in °C
      char message[20];
      sprintf(message, "Temperature: %.1f", tempC);
      Serial.println(tempC);
      client.publish("esp/temp", message);

   
      }


  }
}
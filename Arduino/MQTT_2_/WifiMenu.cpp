#include "WifiMenu.h"
#include "Arduino.h"



WifiMenu::WifiMenu( LiquidCrystal_I2C lcd, int BUTTON_Menu, int BUTTON_Choise)
: _BUTTON_Menu(BUTTON_Menu),
  _BUTTON_Choise(BUTTON_Choise),
  _lcd(lcd),
  ssid1(""), 
  wifiON(false),
  buttonState_Menu(0),
  buttonState_Choise(0),
  lastButtonState_Menu(0),
  lastButtonState_Choise(0),
  programNumber(0),
  programChoise(0),
  hjemme_ssid("Tomas"),
  hjemme_password("Tomas1974"),
  skole_ssid("POCO X3 Pro"),
  skole_password("Tomas1974")

{ }


void WifiMenu::initialize() {
  
   _lcd.init();                    
   _lcd.backlight();
  pinMode(_BUTTON_Menu, INPUT_PULLUP);
  pinMode(_BUTTON_Choise, INPUT_PULLUP);
  
       
}




void WifiMenu::wifiConnection(String ssid, String password)
{
  int counter=0;
  ssid1=ssid;

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && counter<10) 
  {
    counter++;
    delay(500);
    
  }
  
if (counter==10)
   Serial.println("Ingen forbindelse");
       

else
{
  Serial.println("Connected to the WiFi network");
    wifiON=true;
  
}



}


String WifiMenu::getSsid1()
{
  return ssid1;
}


bool WifiMenu::getwifiON()
{
  return wifiON;
}





void WifiMenu::button_Menu()
{
    
    buttonState_Menu = digitalRead(_BUTTON_Menu);
        
  if (buttonState_Menu != lastButtonState_Menu) {
    

    if (buttonState_Menu == HIGH) {
      
        programNumber++;
        
                     
      if (programNumber==3)
      programNumber=1;

          valg();  
    }

    delay(50); // Debounce delay
  }

  lastButtonState_Menu = buttonState_Menu;
  

}


void WifiMenu::valg()
{
  
  {
     
      _lcd.clear();
   
      if (programNumber==1 )
      {
        
        _lcd.print("  Hjemme WIFI");

        _lcd.setCursor(0,1);
        
        if (getwifiON() && getSsid1()==hjemme_ssid )
        _lcd.print("-------ON-------");
        else
        _lcd.print("------OFF-------");

      }
      

      else
      {
        _lcd.print("   Skole WIFI");
        _lcd.setCursor(0,1);
        if ( getwifiON() &&  getSsid1()==skole_ssid)
        _lcd.print("-------ON-------");
        else
        _lcd.print("------OFF-------");
      }
      
      
  }

}



void WifiMenu::button_Choise()
{
 
 buttonState_Choise = digitalRead(_BUTTON_Choise);

    if (buttonState_Choise != lastButtonState_Choise) 
    if (buttonState_Choise == HIGH) 
    {

    programChoise=programNumber;      
    wifiON=false;
    
      

 
      if (programChoise==1)
      
      wifiConnection(hjemme_ssid, hjemme_password);
      else
      wifiConnection(skole_ssid, skole_password);
      
      valg();
            
    }
     
    lastButtonState_Choise = buttonState_Choise;

}


    void WifiMenu::wifiMenuSystem()
    {
      button_Menu();
      button_Choise();
    }






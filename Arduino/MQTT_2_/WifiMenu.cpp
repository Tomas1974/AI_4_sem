#include "WifiMenu.h"
#include "Arduino.h"



WifiMenu::WifiMenu(LiquidCrystal_I2C lcd, std::vector<WifiModel> wifiNetworks , int BUTTON_Menu, int BUTTON_Choise)
: _lcd(lcd),
 _BUTTON_Menu(BUTTON_Menu),
 _BUTTON_Choise(BUTTON_Choise),
 buttonState_Menu(0),
 buttonState_Choise(0),
 lastButtonState_Menu(0),
 lastButtonState_Choise(0),
 wifiON(""), 
 programNumber(-1)

{
    _wifiNetworks = wifiNetworks; 
}



void WifiMenu::initialize() {
  
  _lcd.init();                    
  _lcd.backlight();
  pinMode(_BUTTON_Menu, INPUT_PULLUP);
  pinMode(_BUTTON_Choise, INPUT_PULLUP);
  
       
}




String WifiMenu::wifiConnection(String ssid, String password)
{
  int counter=0;
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && counter<10) 
  {
    counter++;
    delay(500);
    
  }
  
if (counter==10)
{
   Serial.println("Ingen forbindelse");
   ssid="";
       
}
else

  Serial.println("Connected to the WiFi network");
 

return ssid;

}



void WifiMenu::button_Menu()
{
    
    buttonState_Menu = digitalRead(_BUTTON_Menu);
        
  if (buttonState_Menu != lastButtonState_Menu) {
    

    if (buttonState_Menu == HIGH) {
            

        programNumber++;

      if (programNumber==_wifiNetworks.size())
      programNumber=0;

          valg();  

       
    }
    
  }

  lastButtonState_Menu = buttonState_Menu;
  

}


void WifiMenu::valg()
{
  
       
      _lcd.clear();
      _lcd.print(_wifiNetworks[programNumber].getNetworkName());

      _lcd.setCursor(0,1);
        
      if (getwifiON() == _wifiNetworks[programNumber].getSSID() )
       _lcd.print("-------ON-------");
      else
       _lcd.print("------OFF-------");


}



void WifiMenu::button_Choise()
{
 
 buttonState_Choise = digitalRead(_BUTTON_Choise);

    if (buttonState_Choise != lastButtonState_Choise) 
    if (buttonState_Choise == HIGH) 
    {
             //Her placeres en String i wificonnection. Det sker ved at kalde wificonnection. (Den etablere wifi og sender navnet på opkoblingen retur). Hvis der ikke var netværk er opkoblingen "" tom. 
       setWifiOn(wifiConnection(_wifiNetworks[programNumber].getSSID(), _wifiNetworks[programNumber].getPassword()));
       valg();
             
    }
     
    lastButtonState_Choise = buttonState_Choise;

}


    void WifiMenu::wifiMenuSystem() //Kalde metoden fra main
    {
      button_Menu();
      button_Choise();
    }




String WifiMenu::getwifiON()
{
  return wifiON;
}

void WifiMenu::setWifiOn(String wifiON1)
{
  wifiON=wifiON1;
}



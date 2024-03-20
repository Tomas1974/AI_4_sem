// WifiMenu.h
#ifndef WifiMenu_h
#define WifiMenu_h

#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include "WifiModel.h"
#include <vector>


class WifiMenu {
public:
    WifiMenu(LiquidCrystal_I2C lcd, std::vector<WifiModel> wifiNetworks, int BUTTON_Menu, int BUTTON_Choise);
    void initialize();        // Initializes the LCD
    String getwifiON();
    void wifiMenuSystem();

private:

    String wifiConnection(String ssid, String password);
    void button_Menu();
    void valg();
    void button_Choise();
    void setWifiOn(String wifiON1);
    

    LiquidCrystal_I2C _lcd;  // LCD object
    int _BUTTON_Menu;
    int _BUTTON_Choise;
    String wifiON;
    int buttonState_Menu;
    int buttonState_Choise;
    int lastButtonState_Menu;
    int lastButtonState_Choise;
    int programNumber;
    std::vector<WifiModel> _wifiNetworks ;
    
            

};

#endif

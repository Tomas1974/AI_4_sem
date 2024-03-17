// WifiMenu.h
#ifndef WifiMenu_h
#define WifiMenu_h

#include <LiquidCrystal_I2C.h>
#include <WiFi.h>

class WifiMenu {
public:
     WifiMenu(LiquidCrystal_I2C lcd, int BUTTON_Menu, int BUTTON_Choise);
    void wifiConnection(String ssid, String password);
    void initialize();        // Initializes the LCD
    String getSsid1();
    bool getwifiON();
    void wifiMenuSystem();

private:

    void button_Menu();
    void valg();
    void button_Choise();


    LiquidCrystal_I2C _lcd;   // LCD object
    int _BUTTON_Menu;
    int _BUTTON_Choise;
    String ssid1;
    bool wifiON=false;
    
    int buttonState_Menu;
    int buttonState_Choise;
    int lastButtonState_Menu;
    int lastButtonState_Choise;
    int programNumber;
    int programChoise;
    char* hjemme_ssid;
    char* hjemme_password;
    char* skole_ssid; // Corrected line
    char* skole_password;
    
        

};

#endif

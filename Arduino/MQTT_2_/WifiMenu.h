// WifiMenu.h
#ifndef WifiMenu_h
#define WifiMenu_h

#include <LiquidCrystal_I2C.h>
#include <WiFi.h>

class WifiMenu {
public:
     WifiMenu(LiquidCrystal_I2C lcd, const char* hjemme_ssid, const char* hjemme_password, const char* skole_ssid, const char* skole_password, int BUTTON_Menu, int BUTTON_Choise);
    void wifiConnection(String ssid, String password);
    void initialize();        // Initializes the LCD
    String getSsid1();
    String getwifiON();
    void wifiMenuSystem();

private:

    void button_Menu();
    void valg();
    void button_Choise();
    void setWifiOn(String wifiON1);

    LiquidCrystal_I2C _lcd;   // LCD object
    int _BUTTON_Menu;
    int _BUTTON_Choise;
    String wifiON;
    int buttonState_Menu;
    int buttonState_Choise;
    int lastButtonState_Menu;
    int lastButtonState_Choise;
    int programNumber;
    const char* _hjemme_ssid;
    const char* _hjemme_password;
    const char* _skole_ssid;
    const char* _skole_password;
    
    
        

};

#endif

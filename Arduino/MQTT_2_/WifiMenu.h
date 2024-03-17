// WifiMenu.h
#ifndef WifiMenu_h
#define WifiMenu_h

#include <LiquidCrystal_I2C.h>
#include <WiFi.h>

class WifiMenu {
public:
     WifiMenu(int BUTTON_Menu, int BUTTON_Choise);
    void initialize();        // Initializes the LCD
    

private:
    LiquidCrystal_I2C _lcd;   // LCD object
    int _BUTTON_Menu;
    int _BUTTON_Choise;
    uint8_t _lcdAddr;
    int _lcdCols;
    int _lcdRows;
};

#endif

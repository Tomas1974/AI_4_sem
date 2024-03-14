#include "WifiMenu.h"




WifiMenu::WifiMenu(uint8_t lcdAddr, int lcdCols, int lcdRows, int BUTTON_Menu, int BUTTON_Choise)
: _lcd(lcdAddr, lcdCols, lcdRows), _BUTTON_Menu(BUTTON_Menu), _BUTTON_Choise(BUTTON_Choise)
{ }


void WifiMenu::initialize() {
    _lcd.init();                    
    _lcd.backlight();
    pinMode(_BUTTON_Menu, INPUT_PULLUP);
    pinMode(_BUTTON_Choise, INPUT_PULLUP);
}
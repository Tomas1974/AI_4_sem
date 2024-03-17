#include "WifiMenu.h"




WifiMenu::WifiMenu( int BUTTON_Menu, int BUTTON_Choise)
: _lcd(_lcdAddr, _lcdCols, _lcdRows), _BUTTON_Menu(BUTTON_Menu), _BUTTON_Choise(BUTTON_Choise), _lcdAddr(0x27), _lcdCols(16), _lcdRows(2)
{ }


void WifiMenu::initialize() {
    _lcd.init();                    
    _lcd.backlight();
    pinMode(_BUTTON_Menu, INPUT_PULLUP);
    pinMode(_BUTTON_Choise, INPUT_PULLUP);
}
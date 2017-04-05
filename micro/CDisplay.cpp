#include "CDisplay.h"

CDisplay::CDisplay(CController* controller) : CTask(controller) {
  _lcd = new LiquidCrystal_I2C(0x27,16,2);

  #ifndef __NODEBUG__
      Serial.println(F("LCD SETUP"));
  #endif
  
  
  _lcd->init();
  _lcd->createChar(0, symbolG);
  _lcd->createChar(1, symbolX);
  _lcd->createChar(2, symbolO);  
  _lcd->createChar(3, symbolT);   
  _lcd->backlight();
  _lcd->setCursor(0, 0);
  _lcd->write(2);
   
  _lcd->print(" XBC 00000000 ");

  _lcd->write(2);

  _lcd->setCursor(0, 1);
  _lcd->write(1);
  _lcd->print(" ");
  _lcd->write(0);
  _lcd->print("BC 00000000 ");
  _lcd->write(3);  

}



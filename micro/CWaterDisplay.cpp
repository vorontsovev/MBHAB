#include "CWaterDisplay.h"

CWaterDisplay::CWaterDisplay(CController* controller, uint8_t vs_address, uint8_t cw_address, uint8_t hw_address) : CTask(controller) {
  _lcd = new LiquidCrystal_I2C(0x27,16,2);

  #ifndef __NODEBUG__
      Serial.println(F("CREATE CWaterDisplay"));
  #endif
  
  
  _lcd->init();
  _lcd->createChar(0, symbolG);
  _lcd->createChar(1, symbolX);
  _lcd->createChar(2, symbolO);  
  _lcd->createChar(3, symbolT);   
  _lcd->backlight();
  _lcd->setCursor(0, 0);
  _lcd->write(2);
   
  _lcd->print(F(" XBC 00000000 "));

  _lcd->write(2);

  _lcd->setCursor(0, 1);
  _lcd->write(1);
  _lcd->print(" ");
  _lcd->write(0);
  _lcd->print("BC 00000000 ");
  _lcd->write(3);  

}

void CWaterDisplay::writeChar(uint8_t x, uint8_t y, uint8_t ch) {
  _lcd->setCursor(x, y);
  _lcd->write(ch);
}

void CWaterDisplay::drawCounter(uint8_t y, uint32_t value) {
  char _counter[8];
  sprintf(_counter, "%08d", value);
  _lcd->setCursor(6, y);
  _lcd->print(_counter);
}

void CWaterDisplay::drawValveState(uint16_t valveState) {
  switch (valveState) {
case 0:
    writeChar(0, 0, 1);
    writeChar(0, 1, 1);    
    writeChar(15, 0, 1);
    break;            
case 1:
    writeChar(0, 0, 2);
    writeChar(0, 1, 1);    
    writeChar(15, 0, 2);
    break;
case 2:
    writeChar(0, 0, 2);
    writeChar(0, 1, 2);    
    writeChar(15, 0, 1);
    break;
  }
}

void CWaterDisplay::onchange() {
  uint32_t _counter;
  uint16_t _vs;
  Serial.println(F("CWaterDisplay.onchange"));

  if (_controller->registers.isChanged(MB_HOLDINGS | 0x00)) {
    _controller->registers.get(0x00, &_vs);
    drawValveState(_vs);
  }
  if (_controller->registers.isChanged(MB_HOLDINGS32 | 0x01)) {
    _controller->registers.get(0x01, &_counter);
    drawCounter(0, _counter);
  }
  if (_controller->registers.isChanged(MB_HOLDINGS32 | 0x03)) {
    _controller->registers.get(0x03, &_counter);
    drawCounter(1, _counter);
  }
}



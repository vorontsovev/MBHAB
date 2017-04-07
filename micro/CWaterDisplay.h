#ifndef _CDISPLAY_H
#define _CDISPLAY_H

#define _CWATERDISPLAY 0x0005

#include <LiquidCrystal_I2C.h>
#include "CController.h"


struct CWaterDisplayInit {
  uint16_t type;
  uint8_t vs_address;
  uint8_t cw_address;
  uint8_t hw_address; 
};

const uint8_t symbolG[8] = {
 0b11111,
 0b10000,
 0b10000,
 0b10000,
 0b10000,
 0b10000,
 0b10000,
 0b00000
};

const uint8_t symbolX[8] = {
 0b00000,
 0b10001,
 0b01010,
 0b00100,
 0b01010,
 0b10001,
 0b00000,
 0b00000
};

const uint8_t symbolO[8] = {
 0b00000,
 0b01110,
 0b10001,
 0b10101,
 0b10001,
 0b01110, 
 0b00000,
 0b00000
};

const uint8_t symbolT[8] = {
 0b00000,
 0b01000,
 0b10100,
 0b00101,
 0b00010, 
 0b00000,
 0b00000,
 0b00000 
};


class CWaterDisplay: public CTask {
private:
  LiquidCrystal_I2C* _lcd;  
  void writeChar(uint8_t x, uint8_t y, uint8_t ch);
  void drawValveState(uint16_t valveState);
  void drawCounter(uint8_t y, uint32_t value);
public:  
  CWaterDisplay(CController* controller, uint8_t vs_address, uint8_t cw_address, uint8_t hw_address);
  void onchange();
};

#endif


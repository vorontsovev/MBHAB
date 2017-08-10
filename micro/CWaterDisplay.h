#ifndef _CDISPLAY_H
#define _CDISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <CTask.h>
#include <CController.h>

struct CWaterDisplayInit {
  uint16_t type;
  uint8_t vs_address;
  uint8_t bm_address;
  uint8_t em_address;
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
  uint8_t _vs_address;
  uint8_t _cw_address;
  uint8_t _hw_address;
  uint8_t _bm_address;
  uint8_t _em_address;
  LiquidCrystal_I2C* _lcd;  
  void writeChar(uint8_t x, uint8_t y, uint8_t ch);
  void drawValveState(uint16_t valveState);
  void drawCounter(uint8_t y, uint32_t value);
  void drawBoilMode(bool bm);
public:  
  CWaterDisplay(CController* controller, uint8_t vs_address, uint8_t bm_address, uint8_t em_address, uint8_t cw_address, uint8_t hw_address);
  void onchange();
};

#endif


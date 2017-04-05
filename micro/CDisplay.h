#ifndef _CDISPLAY_H
#define _CDISPLAY_H

#include <LiquidCrystal_I2C.h>
#include "CController.h"

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


class CDisplay: public CTask {
private:
  LiquidCrystal_I2C* _lcd;  
public:  
  CDisplay(CController* controller);
};

#endif


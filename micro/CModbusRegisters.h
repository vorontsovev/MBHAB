#ifndef _CMODBUSREGISTERS_H
#define _CMODBUSREGISTERS_H

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <bitset>


#define   MB_COILS      0x00
#define   MB_HOLDINGS   0x40
#define   MB_HOLDINGS32 0x80 


class CModbusRegisters {
private:

  uint16_t _low;  
  uint8_t _address32;
  bool  _low_writed;
  
  std::bitset<64> _coils_mask;
  std::bitset<32> _holdings_mask;
   
  std::bitset<64> _coils_changed;
  std::bitset<32> _holdings_changed;

  std::bitset<32> _need_save;
  
  bool isBinded(uint8_t regtype, uint8_t address);
public:
  std::bitset<64> _coils;
  uint16_t _holdings[32];
  
  CModbusRegisters();
  
  bool isChanged();
  bool isChanged(uint8_t reg);
  bool isWriting(uint8_t reg);

  uint8_t set(uint8_t address, bool value);
  uint8_t set(uint8_t address, uint16_t value);
  uint8_t set(uint8_t reg, uint32_t value);

  uint8_t get(uint8_t address, bool& value);
  uint8_t get(uint8_t address, uint16_t& value);
  uint8_t get(uint8_t address, uint32_t& value);  
  
  uint8_t bind(uint8_t regtype, uint8_t address);

  void requestInit(uint8_t reg);
  bool isInited(uint8_t reg);

  void reset();
};

#endif

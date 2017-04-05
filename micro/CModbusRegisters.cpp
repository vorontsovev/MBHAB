#include "CModbusRegisters.h"
#include <Arduino.h>

CModbusRegisters::CModbusRegisters() {
  _coils.reset();
  _coils_changed.reset();
  _holdings_changed.reset();
  _coils_mask.reset();
  _holdings_mask.reset();
};


// Сброс статусов об изменении регистров
void CModbusRegisters::reset() {
  _coils_changed.reset();
  _holdings_changed.reset();
}

// Возврат статуса изменения для регистра
boolean CModbusRegisters::isChanged(uint8_t reg) {
  uint8_t _address = reg & 0x3F;
  uint8_t _regtype = reg & 0xC0;

  #ifndef __NODEBUG__
    Serial.print(F("CHANGE REG="));
    Serial.println(reg, HEX);
  #endif
  
  switch (_regtype) {
case MB_COILS:
    return (1==_coils_changed[_address]);
    break;
case MB_HOLDINGS:
    return (1==_holdings_changed[_address]);
    break;
case MB_HOLDINGS32:
    return ((1==_holdings_changed[_address]) | (_holdings_changed[_address+1]));
    break;
  }
  return false;
}

bool CModbusRegisters::isBinded(uint8_t regtype, uint8_t address) {
  if ((address < 32) | ((regtype == MB_HOLDINGS32) & (address < 31))) {
    switch (regtype) {
case MB_COILS:
      return _coils_mask[address];
case MB_HOLDINGS:
      return _holdings_mask[address];
case MB_HOLDINGS32:
      return (_holdings_mask[address] | _holdings_mask[address+1]);        
    }
  }
  return false;
}

// Резервирование регистра
uint8_t CModbusRegisters::bind(uint8_t regtype, uint8_t address) {

  #ifndef __NODEBUG__
    Serial.print("BIND ADDRESS=");
    Serial.print(address, HEX);
    Serial.print(" REGTYPE=");
    Serial.println(regtype, HEX);
  #endif

  if (!isBinded(regtype, address)) {
    switch (regtype) {
      
case MB_COILS:    // coil bind
      #ifndef __NODEBUG__
        Serial.println("BIND SUCESS");
      #endif
      _coils_mask[address] = 1;
      return MB_COILS | address;
      
case MB_HOLDINGS:    // holding bind
      _holdings_mask[address] = 1;
      #ifndef __NODEBUG__
        Serial.println("BIND SUCESS");
      #endif
      return MB_HOLDINGS | address;

case MB_HOLDINGS32:    //  holding32 bind
      _holdings_mask[address] = 1;
      _holdings_mask[address+1] = 1;

      #ifndef __NODEBUG__
        Serial.println("BIND SUCESS");
      #endif
       
      return MB_HOLDINGS32 | address;
    }
  }
  
  #ifndef __NODEBUG__
    Serial.println("BIND CRASH");
  #endif

  return 0xFF;    // Устанавливаем два верхних бита в ответе для неудачи
}

uint8_t CModbusRegisters::set(uint8_t address, bool value) {
  #ifndef __NODEBUG__
    Serial.println(F("SET COIL"));
    Serial.print(F("ADDRESS="));
    Serial.println(address);    
    Serial.print(F("VALUE="));
    Serial.println(value);    
  #endif
  
  if (isBinded(MB_COILS, address)) {
    if (_coils[address] != value) {
      _coils[address] = value;
      _coils_changed[address] = 1;
      #ifndef __NODEBUG__
        Serial.println("COIL CHANGED");
      #endif
    }
    #ifndef __NODEBUG__
      Serial.println("COIL NOT CHANGED");
    #endif
    return 0;
  }
  #ifndef __NODEBUG__
    Serial.println("COIL CHANGE CRASH");
  #endif

  return 1;
}

uint8_t CModbusRegisters::set(uint8_t address, uint16_t value) {
  #ifndef __NODEBUG__
    Serial.println(F("SET HOLDING"));
    Serial.print(F("ADDRESS="));
    Serial.println(address);    
    Serial.print(F("VALUE="));
    Serial.println(value, HEX);    
  #endif

  if (isBinded(MB_HOLDINGS, address)) {
    if (_holdings[address] != value) {
      _holdings[address] = value;
      _holdings_changed[address] = 1;
      #ifndef __NODEBUG__
        Serial.println("COIL CHANGED");
      #endif
    }
    return 0;
  }
  return 1;
}

uint8_t CModbusRegisters::set(uint8_t address, uint32_t value) {
  #ifndef __NODEBUG__
    Serial.println(F("SET HOLDING32"));
    Serial.print(F("ADDRESS="));
    Serial.println(address);    
    Serial.print(F("VALUE="));
    Serial.println(value, HEX);    
  #endif

  if (isBinded(MB_HOLDINGS32, address)) {
    uint32_t _regval = _holdings[address] << 16 | _holdings[address+1];
    if (_regval != value) {
      _holdings[address] = ((uint16_t*)(&value))[0];
      _holdings[address+1] = ((uint16_t*)(&value))[1];
      _holdings_changed[address] = 1;
      _holdings_changed[address+1] = 1;
    }
    return 0;
  }
  return 1;
}


uint8_t CModbusRegisters::get(uint8_t address, bool* value) {
  #ifndef __NODEBUG__
    Serial.println(F("GET COILS"));
    Serial.print(F("ADDRESS="));
    Serial.println(address);    
  #endif

  if (isBinded(MB_COILS, address)) {
    *value = _coils[address];
    return 0;
  }
  return 1;    
}

uint8_t CModbusRegisters::get(uint8_t address, uint16_t* value) {
  #ifndef __NODEBUG__
    Serial.println(F("GET HOLDINGS"));
    Serial.print(F("ADDRESS="));
    Serial.println(address);    
  #endif

  if (isBinded(MB_HOLDINGS, address)) {
    *value = _holdings[address];
    return 0;
  }
  return 1;    
}

uint8_t CModbusRegisters::get(uint8_t address, uint32_t* value) {
  #ifndef __NODEBUG__
    Serial.println(F("GET HOLDINGS"));
    Serial.print(F("ADDRESS="));
    Serial.println(address);    
  #endif

  if (isBinded(MB_HOLDINGS32, address)) {
    *value = _holdings[address] << 16 | _holdings[address+1];
    return 0;
  }
  return 1;      
}


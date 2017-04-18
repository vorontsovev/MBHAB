#include "CModbusRTUConnector.h"

extern int __bss_end;
extern void *__brkval;

int memoryFree()
{
   int freeValue;
   if((int)__brkval == 0)
      freeValue = ((int)&freeValue) - ((int)&__bss_end);
   else
      freeValue = ((int)&freeValue) - ((int)__brkval);
   return freeValue;
}


uint16_t CRC16_2(uint8_t *buf, uint8_t len)
{  
  uint16_t crc = 0xFFFF;
  for (int pos = 0; pos < len; pos++)
  {
    crc ^= (uint8_t)buf[pos];    // XOR byte into least sig. byte of crc

    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
    else                            // Else LSB is not set
      crc >>= 1;                    // Just shift right
    }
  }
  return crc;
}


boolean checkCRC(uint8_t *buf, uint8_t len, uint16_t CRC) {
  boolean _result = ((buf[len-1] == ((uint8_t*)(&CRC))[1]) &  (buf[len-2] == ((uint8_t*)(&CRC))[0]));
  
  #ifndef __NODEBUG__  
    Serial.print("CRCLo = ");
    Serial.println(buf[len-1], HEX);
    Serial.print("CRCHi = ");
    Serial.println(buf[len-2], HEX);
    Serial.print("CRC = ");
    Serial.println(CRC, HEX);
    if (!_result)  {
      Serial.println("CRC ERROR");
    } else {
      Serial.println("CRC OK");
    }
  #endif
  return _result;
}

CModbusRTUConnector::CModbusRTUConnector(CController* controller, uint8_t rx, uint8_t tx, uint32_t rate):CTask(controller) {

  #ifndef __NODEBUG__
      Serial.println(F("CREATE CModbusRTUConnector"));
      Serial.print(F("rx="));
      Serial.println(rx);
      Serial.print(F("tx="));
      Serial.println(tx);
      Serial.print(F("rate="));
      Serial.println(rate);
  #endif
  
  _serial = new SoftwareSerial(rx, tx);
  _serial->begin(rate);
}

void CModbusRTUConnector::run() {
  if (_serial->available()) {
    receiveSerialPacket();
    uint16_t CRC = CRC16_2(_modbusbuffer, _modbuslength-2);
    if (checkCRC(_modbusbuffer, _modbuslength, CRC)) {
      switch (_modbusbuffer[1]) {
case MB_CMD_READ_DO:
        readDO();
        break;
case MB_CMD_READ_DI:
        readDI();
        break;
case MB_CMD_READ_AO:
        readAO();
        break;
case MB_CMD_READ_AI:
        readAI();
        break;
case MB_CMD_WRITE_DO:
        writeDO();
        break;
case MB_CMD_WRITE_AO:
        writeAO();
        break;
case MB_CMD_WRITE_MULTIPLE_AO:
        writeAO32();
        break;        
default:
        modbusError(1);
        break;
      }
    }
  }
}

void CModbusRTUConnector::readDO() {
  uint16_t _count = _modbusbuffer[4] << 8 | _modbusbuffer[5];
  
  #ifndef __NODEBUG___
    Serial.println(F("read DO"));
    Serial.print(F("address = "));
    Serial.println(_modbusbuffer[3], HEX);    
    Serial.print(F("count = "));
    Serial.println(_count, HEX);    
  #endif
  
  if (_count != 1) {
    if ((32 == _count) & (32 == _modbusbuffer[3])) {      // Для специального адреса MODBUS 32 интерпретируем команду как запрос статусов инициализации
      uint32_t _reqStatus;
      _controller->registers.getRequestStatus(&_reqStatus);
      _modbusbuffer[2] = 4;
      _modbusbuffer[3] = ((uint8_t*)(&_reqStatus))[3];
      _modbusbuffer[4] = ((uint8_t*)(&_reqStatus))[2];
      _modbusbuffer[5] = ((uint8_t*)(&_reqStatus))[1];      
      _modbusbuffer[6] = ((uint8_t*)(&_reqStatus))[0];
      sendSerialPacket(_modbusbuffer, 7);
    } else {
      modbusError(3);
    }
  } else {
    bool _reg;
    if (_controller->registers.get(_modbusbuffer[3], &_reg)) {
      _modbusbuffer[2] = 1;
      _modbusbuffer[3] = _reg;
      sendSerialPacket(_modbusbuffer, 4);
    }
  }
}

void CModbusRTUConnector::readDI() {
  
}

void CModbusRTUConnector::readAI() {
  uint16_t _count = _modbusbuffer[4] << 8 | _modbusbuffer[5];
  if (_count != 1) {
    modbusError(3);
  } else {
    uint16_t _res = 0;
    if (_controller->registers.get(_modbusbuffer[3], &_res)) {
      _modbusbuffer[2] = 1;

      _modbusbuffer[3] = ((uint8_t*)(&_res))[1];
      _modbusbuffer[4] = ((uint8_t*)(&_res))[0];
      sendSerialPacket(_modbusbuffer, 5); 
    }
  }  
}

void CModbusRTUConnector::readAO() {
  uint8_t _address;
  uint16_t _count = _modbusbuffer[4] << 8 | _modbusbuffer[5];

  #ifndef __NODEBUG___
    Serial.println(F("read AO"));
    Serial.print(F("address = "));
    Serial.println(_modbusbuffer[3], HEX);    
    Serial.print(F("count = "));
    Serial.println(_count, HEX);    
  #endif

  switch (_count) {
case 1:
    uint16_t _reg;
    if (!_controller->registers.get(_modbusbuffer[3], &_reg)) {    
      _modbusbuffer[2] = 2;
      _modbusbuffer[3] = ((uint8_t*)(&_reg))[1];
      _modbusbuffer[4] = ((uint8_t*)(&_reg))[0];
      sendSerialPacket(_modbusbuffer, 5);
    } else modbusError(0x02);
    break;
case 2:
    uint32_t _reg32;
    if (!_controller->registers.get(_modbusbuffer[3], &_reg32)) {    
      _modbusbuffer[2] = 4;
      _modbusbuffer[3] = ((uint8_t*)(&_reg32))[3];
      _modbusbuffer[4] = ((uint8_t*)(&_reg32))[2];
      _modbusbuffer[5] = ((uint8_t*)(&_reg32))[1];      
      _modbusbuffer[6] = ((uint8_t*)(&_reg32))[0];            
      sendSerialPacket(_modbusbuffer, 7);
    } else modbusError(0x02);
    break;
default:
    modbusError(0x03);
    break;
  }
}

// Запись дискретного выхода
void CModbusRTUConnector::writeDO() {
  bool _reg;
  uint8_t _address = _modbusbuffer[3];
  if (0xFF == _modbusbuffer[5]) {
    _reg = true;
  } else {
    _reg = false;
  }
  if (_controller->registers.set(_address, _reg)) {
    sendSerialPacket(_modbusbuffer, 6);
  } else {
    modbusError(3);
  }
}

// Запись аналогового выхода
void CModbusRTUConnector::writeAO() {
#ifndef __NODEBUG___
  Serial.println(F("write AO !!!!!!!!!!!!!!!!!!!!!!!!"));
#endif

  uint8_t _address = _modbusbuffer[3];
  uint16_t _value = _modbusbuffer[4] << 8 | _modbusbuffer[5];
  if (!_controller->registers.set(_address, _value)) {

  #ifndef __NODEBUG___
    Serial.print("_value=");
    Serial.println(_value, HEX);
  #endif
    sendSerialPacket(_modbusbuffer, _modbuslength-2);
  } else {
    modbusError(0x02);
  }
}


// Запись аналогового выхода
void CModbusRTUConnector::writeAO32() {
#ifndef __NODEBUG___
  Serial.println(F("write AO32 !!!!!!!!!!!!!!!!!!!!!!!!"));
#endif

  uint8_t _address = _modbusbuffer[3];
  uint16_t _len = _modbusbuffer[4] << 8 | _modbusbuffer[5];
  if (2 == _len) {
    uint32_t _value;
    ((uint8_t*)(&_value))[3] = _modbusbuffer[7];
    ((uint8_t*)(&_value))[2] = _modbusbuffer[8];    
    ((uint8_t*)(&_value))[1] = _modbusbuffer[9];        
    ((uint8_t*)(&_value))[0] = _modbusbuffer[10];            
    
    if (!_controller->registers.set(_address, _value)) {

    #ifndef __NODEBUG___
      Serial.print("_value=");
      Serial.println(_value, HEX);
    #endif
      sendSerialPacket(_modbusbuffer, _modbuslength-2);
    } else {
      modbusError(0x02);
    }  
  } else {
    modbusError(0x03);    
  }
}

void CModbusRTUConnector::modbusError(uint8_t error) {
  _modbusbuffer[1] = _modbusbuffer[1] | 0x80;
  _modbusbuffer[2] = error;
  sendSerialPacket(_modbusbuffer, 3);
}

void CModbusRTUConnector::receiveSerialPacket() {

  #ifndef __NODEBUG__  
    Serial.print("SER -> ");
  #endif

  bool _complete = false;
  bool _firstbyte = false;
  long _timepoint;
  
  _modbuslength = 0;
  while (!_complete) {
    if (_serial->available()) {
      _firstbyte = true;
      _modbusbuffer[_modbuslength] = _serial->read();

      #ifndef __NODEBUG__  
        Serial.print(_modbusbuffer[_modbuslength], HEX);
        Serial.print(" ");
      #endif

      _modbuslength++;
      _timepoint = millis();
    }
    if (_firstbyte) {
      if ((millis()-_timepoint) > 20) {
        _complete = true;
      }
    }
  }

  #ifndef __NODEBUG__  
    Serial.println();
  #endif
}

void CModbusRTUConnector::sendSerialPacket(uint8_t* buf, uint8_t len) {
  uint16_t CRC = CRC16_2(_modbusbuffer, len);
  #ifndef __NODEBUG__    
    Serial.print(F("FREE MEM="));
    Serial.println(memoryFree(), HEX);
    Serial.print("LEN = ");
    Serial.println(len, HEX);
    Serial.print("SER <- ");
  #endif

  _modbusbuffer[len+1] = ((uint8_t*)(&CRC))[1];
  _modbusbuffer[len] = ((uint8_t*)(&CRC))[0];
  _serial->write(buf, len+2);
  #ifndef __NODEBUG__    
    for (int i=0; i<(len+2); i++) {
      Serial.print(_modbusbuffer[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  #endif
}




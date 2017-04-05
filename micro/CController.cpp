/**
 * CController implementation
 */

#include "CController.h"


uint16_t CRC16_2(uint8_t *buf, int len)
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


boolean checkCRC(uint8_t *buf, int len, uint16_t CRC) {
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

CController::CController(uint8_t RX, uint8_t TX, uint16_t rate) {
  _taskFactory = new CTaskFactory(this);
  _taskManager = new CTaskManager();

  _serial = new SoftwareSerial(RX, TX);
  _serial->begin(rate);
}

void CController::run() {
  if (_serial->available()) {
    receiveSerialPacket();
    uint16_t CRC = CRC16_2(_modbusbuffer, _modbuslength-2);
    if (checkCRC(_modbusbuffer, _modbuslength, CRC)) {
      switch (_modbusbuffer[1]) {
case 1:
        readDO();
        break;
case 2:
        readDI();
        break;
case 3:
        readAO();
        break;
case 4:
        readAI();
        break;
case 5:
        writeDO();
        break;
case 6:
        writeAO();
        break;
default:
        modbusError(1);
        break;
      }
    }
  }
  _taskManager->run();
  _taskManager->onchange();
  registers.reset();
}

void CController::readDO() {
  uint16_t _count = _modbusbuffer[4] << 8 | _modbusbuffer[5];
  if (_count != 1) {
    modbusError(3);
  } else {
    bool _reg;
    if (registers.get(_modbusbuffer[3], &_reg)) {
      _modbusbuffer[2] = 1;
      _modbusbuffer[3] = _reg;
      sendSerialPacket(_modbusbuffer, _reg);
    }
  }
}

void CController::readDI() {
  
}

void CController::readAI() {
  uint16_t _count = _modbusbuffer[4] << 8 | _modbusbuffer[5];
  if (_count != 1) {
    modbusError(3);
  } else {
    uint16_t _res = 0;
    if (registers.get(_modbusbuffer[3], &_res)) {
      _modbusbuffer[2] = 1;

      _modbusbuffer[3] = ((uint8_t*)(&_res))[1];
      _modbusbuffer[4] = ((uint8_t*)(&_res))[0];
      sendSerialPacket(_modbusbuffer, 5); 
    }
  }  
}

void CController::readAO() {
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
    if (!registers.get(_modbusbuffer[3], &_reg)) {    
      _modbusbuffer[2] = 2;
      _modbusbuffer[3] = ((uint8_t*)(&_reg))[1];
      _modbusbuffer[4] = ((uint8_t*)(&_reg))[0];
      sendSerialPacket(_modbusbuffer, 5);
    } else modbusError(0x02);
    break;
case 2:
    uint32_t _reg32;
    if (!registers.get(_modbusbuffer[3], &_reg32)) {    
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
void CController::writeDO() {
  bool _reg;
  uint8_t _address = _modbusbuffer[3];
  if (0xFF == _modbusbuffer[5]) {
    _reg = true;
  } else {
    _reg = false;
  }
  if (registers.set(_address, _reg)) {
    sendSerialPacket(_modbusbuffer, 6);
  } else {
    modbusError(3);
  }
}

// Запись аналогового выхода
void CController::writeAO() {
#ifndef __NODEBUG___
  Serial.println(F("write AO !!!!!!!!!!!!!!!!!!!!!!!!"));
#endif

  uint8_t _address = 0x40 | _modbusbuffer[3];
  uint16_t _reg = _modbusbuffer[4] << 8 | _modbusbuffer[5];;
  if (!registers.set(_address, _reg)) {

  #ifndef __NODEBUG___
    Serial.print("_reg=");
    Serial.println(_reg);
  #endif
    sendSerialPacket(_modbusbuffer, _modbuslength-2);
  } else {
    modbusError(0x02);
  }
}

void CController::modbusError(uint8_t error) {
  _modbusbuffer[1] = _modbusbuffer[1] | 0x80;
  _modbusbuffer[2] = error;
  sendSerialPacket(_modbusbuffer, 3);
}


void CController::setup() {

}

void CController::setActive() {

}


void CController::receiveSerialPacket() {

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

void CController::sendSerialPacket(uint8_t* buf, uint8_t len) {
  uint16_t CRC = CRC16_2(_modbusbuffer, len);
  #ifndef __NODEBUG__    
    Serial.print("CRC = ");
    Serial.println(CRC, HEX);
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

void CController::createTask(void* initdata) {
  uint16_t _type = *((uint16_t*)initdata);

  #ifndef __NODEBUG__
    Serial.print(F("CREATE TASK "));
    Serial.print(F("TYPE="));
    Serial.println(_type, HEX);  
  #endif

  switch (_type) {
case _CBMP180SENSOR:
    _taskManager->addTask(_taskFactory->createBMP180Sensor(initdata));
    break;
case _CWATERRELAY:
    _taskManager->addTask(_taskFactory->createWaterRelay(initdata));
    break;
  }
  
/*  if (type.equals(BMP180Sensor)) {
    _taskManager->addTask(_taskFactory->createBMP180Sensor(name, &root));
  } else {
    if (type.equals(WaterCounter))  {
      _taskManager->addTask(_taskFactory->createWaterCounter(name, &root));
    } else {
      if (type.equals(WaterRelay)) {
        _taskManager->addTask(_taskFactory->createWaterRelay(name, &root));
      }
    }
  }*/
}


void CController::destroyTask(CTask task) {

}

void CController::allocatePin() {

}

void CController::deallocatePin() {

}

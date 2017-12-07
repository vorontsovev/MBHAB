#include <CModbusRTUConnector.h>

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

uint16_t CRC16_cicle(uint16_t crc, uint8_t b) {
  crc ^= b;
  for (int i = 8; i != 0; i--) {
    if ((crc & 0x0001) != 0) {
      crc >>= 1;
      crc ^= 0xA001;
    } else {
      crc >>= 1;      
    }
  }
  return crc;
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
  #ifndef __NODEBUG__
    Serial.print(F("CRC="));
    Serial.println(crc, HEX);
  #endif
  
  return crc;
}

uint16_t swap(uint16_t b) {
  return ((b & 0xFF) << 8) + ((b >> 8) & 0xFF);
}


void timePrint() {
  long t = millis();
  int time=t/1000;
  if (time/60/60<10) { Serial.print ("0"); }
  Serial.print (time/60/60);
  Serial.print (":");
  if (time/60%60<10) { Serial.print ("0"); }
  Serial.print ((time/60)%60);
  Serial.print (":");
  if (time%60<10) { Serial.print ("0"); }
  Serial.print (time%60);
  Serial.print (".");
  if (t%1000<10) { Serial.print ("00"); } else if (t%1000<100) { Serial.print ("0"); };
  Serial.print (t%1000);  
  Serial.print(" ");
}

CModbusRTUConnector::CModbusRTUConnector(CController* controller, uint8_t id, uint16_t timeout, int8_t rx, uint8_t tx, uint8_t re, uint8_t de, uint32_t rate):CTask(controller) {

  #ifndef __NODEBUG__
      Serial.println(F("CREATE CModbusRTUConnector"));
      Serial.print(F("rx="));
      Serial.println(rx);
      Serial.print(F("tx="));
      Serial.println(tx);
      Serial.print(F("rate="));
      Serial.println(rate);
  #endif

  _id = id;
  _re = re;
  _de = de;
  pinMode(_re, OUTPUT);
  
  digitalWrite(_re, LOW);
  
  _init = false;
  _timeout = timeout;
  _serial = new SoftwareSerial(rx, tx);
  _serial->begin(rate);
  _last_request = millis();
}

void CModbusRTUConnector::run() {
  bool _status;
  _controller->registers.get(0x00, _status);


  if (_serial->available()) {
    if (_status) {
      _controller->registers.set(0x00, false);
    }

    CModbusCommand _cmd;
    
    if (0 == receiveSerialPacket(&_cmd)) {

      if (_cmd.id == this->_id) {

		#ifndef __NODEBUG__
			Serial.print(F("id="));
			Serial.println(_cmd.id, HEX);
			Serial.print(F("command="));
			Serial.println(_cmd.command, HEX);
			Serial.print(F("address="));
			Serial.println(_cmd.address, HEX);
			Serial.print(F("data="));
			Serial.println(_cmd.data, HEX);
			Serial.print(F("crc="));
			Serial.println(_cmd.crc, HEX);
		#endif
		
		_last_request = millis();		  

		switch (_cmd.command) {
case MB_CMD_READ_DO:
			readDO(&_cmd);
			break;
case MB_CMD_READ_DI:
			readDO(&_cmd);
			break;
case MB_CMD_READ_AO:
			if (_init) {
				readAO(&_cmd);
			}
			break;
case MB_CMD_READ_AI:
			if (_init) {
				readAO(&_cmd);
			}
			break;
case MB_CMD_WRITE_DO:
			writeDO(&_cmd);
			break;
case MB_CMD_WRITE_AO:
			writeAO(&_cmd);
			break;
default:
			modbusError(&_cmd, 1);
			break;
		}
	  }
	}
  }
  if ((millis() - _last_request) > _timeout) {
    if (!_status) {
      _controller->registers.set(MB_COILS | 0x00, true);
      Serial.println(F("OFFLINE !!!"));
    }
  }  
}

void CModbusRTUConnector::readDO(CModbusCommand* cmd) {
  _init = true;
  #ifndef __NODEBUG__  
	timePrint();
    Serial.println(F("CModbusRTUConnector::readDO"));
  #endif
    
  beginWrite();
  write((uint8_t*)cmd, 2);      
  uint8_t len = cmd->data >> 3;
  if (cmd->data & 0x07 > 0) len++;
  write(&len, 1);
  uint8_t _bitbyte = 0;
  uint8_t _counter = 0;

  for (int i=cmd->address; i<(cmd->address+cmd->data); i++) {
    _bitbyte = _bitbyte | (_controller->registers._coils[i] << _counter);
    _counter++;
    if (8 ==_counter) {
      _counter = 0;
      write(&_bitbyte, 1);
      _bitbyte = 0;
    }
  }
  writeCRC();
  timePrint();
}

// Чтение аналоговых регистров
void CModbusRTUConnector::readAO(CModbusCommand* cmd) {
  #ifndef __NODEBUG__  
    Serial.println(F("CModbusRTUConnector::readAO"));
  #endif

  beginWrite();
  write((uint8_t*)cmd, 2);      
  uint8_t len = cmd->data << 1;
  write(&len, 1);
  for (int i=cmd->address; i<(cmd->address+cmd->data); i++) {
    uint16_t reg = _controller->registers._holdings[i];
    reg = swap(reg);
    write((uint8_t*)&reg, 2);
  }
  writeCRC();
}

// Запись дискретных регистров
void CModbusRTUConnector::writeDO(CModbusCommand* cmd) {
  #ifndef __NODEBUG__  
    Serial.println(F("CModbusRTUConnector::writeDO"));
  #endif

  bool _reg;
  if (0xFF00 == cmd->data) {
    _reg = true;
  } else {
    _reg = false;
  }
  if (!_controller->registers.set(cmd->address, _reg)) {
    cmd->address = swap(cmd->address);
    cmd->data = swap(cmd->data);
    beginWrite();
    write((uint8_t*)cmd, 6);
    writeCRC();
  } else {
    modbusError(cmd, 3);
  }
}

// Запись аналоговых регистров
void CModbusRTUConnector::writeAO(CModbusCommand* cmd) {
  #ifndef __NODEBUG__  
    Serial.println(F("CModbusRTUConnector::writeAO"));
  #endif

  if (!_controller->registers.set(cmd->address, cmd->data)) {

    cmd->address = swap(cmd->address);
    cmd->data = swap(cmd->data);

    beginWrite();
    write((uint8_t*)cmd, 6);
    writeCRC();
  } else {
    modbusError(cmd, 0x02);
  }
}


void CModbusRTUConnector::modbusError(CModbusCommand* cmd, uint8_t error) {
  #ifndef __NODEBUG__
    Serial.println(F("MODBUS ERROR !!!"));
  #endif
  cmd->command = cmd->command | 0x80;
  beginWrite();
  write((uint8_t*)cmd, 2);
  write(&error, 1);
  writeCRC();
}

uint8_t CModbusRTUConnector::receiveSerialPacket(CModbusCommand* cmd) {
  #ifndef __NODEBUG__  
    Serial.print("SER -> ");
  #endif

  long _timepoint;
  uint8_t _counter = 0;

  while (true) {
    if (_serial->available()) {
      ((uint8_t*)(cmd))[_counter] = _serial->read();

      #ifndef __NODEBUG__  
        Serial.print(((uint8_t*)(cmd))[_counter], HEX);
        Serial.print(" ");
      #endif

      _counter++;
      _timepoint = millis();
    }

    if (((millis()-_timepoint) > 60) | (8 == _counter)) {
      
      #ifndef __NODEBUG__  
        Serial.println();
      #endif
    
      if (8 == _counter) {
        
        while (_serial->available()) {    // Сброс хвоста
          uint8_t buf = _serial->read();
        }
        
        uint16_t _crc = CRC16_2(((uint8_t*)cmd), 6);
        if (_crc == cmd->crc) {

          cmd->address = swap(cmd->address);
          cmd->data = swap(cmd->data);
          
          return 0;
        } else {
          return 1;
        }
      } else {
        return 2;
      }
    }
  }
}

void CModbusRTUConnector::beginWrite() {
  _crc = 0xFFFF; 
  digitalWrite(_re, HIGH);
  delay(12);
}

void CModbusRTUConnector::write(uint8_t* buf, uint8_t len) {
  for (int i=0; i< len; i++) {
    _crc = CRC16_cicle(_crc, buf[i]);

    #ifndef __NODEBUG__
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    #endif
  }
  _serial->write(buf, len);
}

void CModbusRTUConnector::writeCRC() {
  uint8_t len;
  len = _serial->write((uint8_t*)&_crc, 2);
  delay(12);
  digitalWrite(_re, LOW);  
  
  #ifndef __NODEBUG__
    _crc = swap(_crc);
    Serial.println(_crc, HEX);  
  #endif
}





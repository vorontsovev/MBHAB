#ifndef _CMODBUSRTUCONNECTOR_H
#define _CMODBUSRTUCONNECTOR_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <CController.h>

#define MB_CMD_READ_DO              0x01
#define MB_CMD_READ_DI              0x02
#define MB_CMD_READ_AO              0x03
#define MB_CMD_READ_AI              0x04
#define MB_CMD_WRITE_DO             0x05
#define MB_CMD_WRITE_AO             0x06

struct CModbusRTUConnectorInit {
  uint16_t type;
  uint16_t timeout;
  uint8_t rx;
  uint8_t tx;
  uint8_t re;
  uint8_t de;
  uint32_t rate;
};

struct CModbusCommand {
  uint8_t id;
  uint8_t command;
  uint16_t address;
  uint16_t data;
  uint16_t crc;
};


class CModbusRTUConnector : public CTask {
private:
  bool _init;
  uint16_t _crc;
  uint32_t _last_request;
  uint16_t _timeout;
  uint8_t _re;
  uint8_t _de;

  SoftwareSerial *_serial;

  uint8_t receiveSerialPacket(CModbusCommand* cmd);
  
  void write(uint8_t* buf, uint8_t len);
  void beginWrite();
  void writeCRC();

  void readDO(CModbusCommand* cmd);
  void readAO(CModbusCommand* cmd);
  void writeDO(CModbusCommand* cmd);
  void writeAO(CModbusCommand* cmd);
  void modbusError(CModbusCommand* cmd, uint8_t error);

public:
  CModbusRTUConnector(CController* controller, uint16_t timeout, int8_t rx, uint8_t tx, uint8_t re, uint8_t de, uint32_t rate);
  void run();
};

#endif

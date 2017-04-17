#ifndef _CMODBUSRTUCONNECTOR_H
#define _CMODBUSRTUCONNECTOR_H

#include <SoftwareSerial.h>
#include "CTask.h"

#define MB_CMD_READ_DO              0x01
#define MB_CMD_READ_DI              0x02
#define MB_CMD_READ_AO              0x03
#define MB_CMD_READ_AI              0x04
#define MB_CMD_WRITE_DO             0x05
#define MB_CMD_WRITE_AO             0x06
#define MB_CMD_WRITE_MULTIPLE_DO    0x0F
#define MB_CMD_WRITE_MULTIPLE_AO    0x10

struct CModbusRTUConnectorInit {
  uint16_t type;
  uint8_t rx;
  uint8_t tx;
  uint32_t rate;
};

class CModbusRTUConnector : public CTask {
private:
  uint8_t _modbusbuffer[64];
  uint8_t _modbuslength;

  SoftwareSerial *_serial;

  void receiveSerialPacket();
  void sendSerialPacket(uint8_t* buf, uint8_t len);

  void readDO();
  void readDI();
  void readAO();
  void readAI();
  void writeDO();
  void writeAO();
  void writeAO32();
  void modbusError(uint8_t error);

public:
  CModbusRTUConnector(CController* controller, uint8_t rx, uint8_t tx, uint32_t rate);
  void run();
};

#endif

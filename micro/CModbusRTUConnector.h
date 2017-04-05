#ifndef _CMODBUSRTUCONNECTOR_H
#define _CMODBUSRTUCONNECTOR_H

#include <SoftwareSerial.h>
#include "CTask.h"

#define _CMODBUSRTUCONNECTOR  0x0003

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
  void modbusError(uint8_t error);

public:
  CModbusRTUConnector(CController* controller, uint8_t rx, uint8_t tx, uint32_t rate);
  void run();
};

#endif

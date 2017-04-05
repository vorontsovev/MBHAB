/**
 * Project Untitled
 */



#ifndef _CCONTROLLER_H
#define _CCONTROLLER_H

#include <Arduino.h>
#include "CTask.h"
#include "CTaskManager.h"
#include "CTaskFactory.h"
#include <SoftwareSerial.h>
#include "CSensor.h"
#include "CModbusRegisters.h"


class CController {
private: 
  uint8_t _RX;
  uint8_t _TX;
  uint8_t _modbusbuffer[64];
  uint8_t _modbuslength;
  SoftwareSerial *_serial;
  CTaskFactory *_taskFactory;
  CTaskManager *_taskManager;
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
  CModbusRegisters registers;

	CController(uint8_t RX, uint8_t TX, uint16_t rate);
	
	void run();
	
	void setup();
	
	void setActive();

	void createTask(void *initdata);
	
	void destroyTask(CTask task);
	
	void allocatePin();
	
	void deallocatePin();

};

#endif //_CCONTROLLER_H

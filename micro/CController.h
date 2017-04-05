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

  CTaskFactory *_taskFactory;
  CTaskManager *_taskManager;

public: 
  CModbusRegisters registers;

	CController();
	
	void run();
	
	void setup();
	
	void setActive();

	void createTask(void *initdata);
	
	void destroyTask(CTask task);
	
	void allocatePin();
	
	void deallocatePin();

};

#endif //_CCONTROLLER_H

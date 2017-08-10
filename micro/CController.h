/**
 * Project Untitled
 */



#ifndef _CCONTROLLER_H
#define _CCONTROLLER_H

#include <Arduino.h>
#include "init.h"
#include "CClasses.h"
#include "CTask.h"
#include "CModbusRegisters.h"

#include "CTaskManager.h"
#include "CTaskFactory.h"

class CTaskFactory;

class CController {

private: 
  CTaskManager *_taskManager;
  CTaskFactory *_taskFactory;

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

#endif // _CCONTROLLER_H

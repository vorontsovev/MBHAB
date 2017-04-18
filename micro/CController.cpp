/**
 * CController implementation
 */

#include "CController.h"

CController::CController() {
  _taskFactory = new CTaskFactory(this);
  _taskManager = new CTaskManager();
}

void CController::run() {
  _taskManager->run();
  if (registers.isChanged()) {
    _taskManager->onchange();
    registers.reset();
  }
}



void CController::setup() {

}

void CController::setActive() {

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
case _CMODBUSRTUCONNECTOR:
    _taskManager->addTask(_taskFactory->createModbusRTUConnector(initdata));
    break;
case _CWATERCOUNTER:    
    _taskManager->addTask(_taskFactory->createWaterCounter(initdata));
    break;
case _CWATERDISPLAY:    
    _taskManager->addTask(_taskFactory->createWaterDisplay(initdata));
    break;
case _CWATCHDOG:    
    _taskManager->addTask(_taskFactory->createWatchdog(initdata));
    break;
case _CRELAY:
    _taskManager->addTask(_taskFactory->createRelay(initdata));  
    break;
case _CTIMER:
    _taskManager->addTask(_taskFactory->createTimer(initdata));  
    break;
  }  
}


void CController::destroyTask(CTask task) {

}

void CController::allocatePin() {

}

void CController::deallocatePin() {

}

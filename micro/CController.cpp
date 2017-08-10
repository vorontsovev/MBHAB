/**
 * CController implementation
 */

#include <CController.h>

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

  _taskManager->addTask(_taskFactory->createTask(initdata));
}


void CController::destroyTask(CTask task) {

}

void CController::allocatePin() {

}

void CController::deallocatePin() {

}

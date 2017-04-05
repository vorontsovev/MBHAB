
#include "CHandleEvent.h"

CHandleEvent::CHandleEvent(CController* controller) {
  _controller = controller;
}

void CHandleEvent::attach(String name) {
  CSensor *sensor = _controller->getSensorByName(name);
  if (sensor) {
     sensor->registerHandleEvent(this);
    #ifndef __NODEBUG__
        Serial.print("attach to ");
        Serial.println(name);  
    #endif
  }
}

void CHandleEvent::handleEvent(CSensor* sensor) {
  
}


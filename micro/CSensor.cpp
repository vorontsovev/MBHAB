
#include "CSensor.h"

/**
 * CSensor implementation
 */


/**
 * @param controller
 * @param name
 */
CSensor::CSensor(CController* controller, String name, int period):CTask(controller, name) {
  _period = period;
  _counter = millis();
  _poll = 0;
}

int CSensor::getPeriod() {
    return _period;
}

void CSensor::run() {
  if (millis() >= (_counter + _period)) {
    _counter = millis();
    poll();
    handleEvents();
  }
}

void CSensor::handleEvents() {
  #ifndef __NODEBUG__
    Serial.println(getName());    
    Serial.println(" handleEvents");
  #endif

  
  _it = _handleEvents.begin();
  while (_it != _handleEvents.end()) {
    (*_it)->handleEvent(this);
    delay(1);
    _it++;
  }
}

void CSensor::registerHandleEvent(CHandleEvent* handleEvent) {
  _handleEvents.push_back(handleEvent);
}

void CSensor::poll() {

}


long CSensor::getLastPoll() {
  return _counter;
}

String CSensor::getValue(String name) {
  
}



/**
 * CSensor implementation
 */


/**
 * @param controller
 * @param name
 */

#include <CSensor.h>

CSensor::CSensor(CController* controller, uint16_t period):CTask(controller) {
  _period = period;
  _counter = millis();
  _poll = 0;
}

uint16_t CSensor::getPeriod() {
    return _period;
}

void CSensor::run() {
  if (millis() >= (_counter + _period)) {
    _counter = millis();
    poll();
  }
}

void CSensor::poll() {

}


uint32_t CSensor::getLastPoll() {
  return _counter;
}



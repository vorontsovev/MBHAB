#include "CTimer.h"

CTimer::CTimer(CController* controller, uint16_t address, uint16_t timeout):CTask(controller) {
  _address = address;
  _timeout = timeout;
  _controller->registers.bind(MB_HOLDINGS32, _address);
}


void CTimer::run() {
  
}

void CTimer::onchange() {
  if (_controller->registers.isChanged(MB_HOLDINGS32 | _address)) {
    _controller->registers.get(_address, &_time);
    time_t t = *(time_t*)(&_time);
    setTime(t);
  }
}



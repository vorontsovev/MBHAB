
#include "CWaterCounter.h"

CWaterCounter::CWaterCounter(CController* controller, uint8_t port, uint8_t c_address):CSensor(controller, 50) {

  #ifndef __NODEBUG__
      Serial.println(F("CREATE CWaterCounter"));
      Serial.print(F("port="));
      Serial.println(port);
      Serial.print(F("address="));
      Serial.println(c_address);
  #endif
    
  _port = port;
  _c_address = c_address;
  _counter = 0;
  _drebezg = 0;
  _prev = analogRead(_port);
  _phase = _prev;
  _controller->registers.bind(MB_HOLDINGS32, _c_address);
  _controller->registers.requestInit(MB_HOLDINGS32 | _c_address);   // Запрос инициализации счетчика от вышестоящей системы
}

void CWaterCounter::poll() {
  boolean _curr = analogRead(_port);

  if (_curr != _prev) {
    _drebezg++;
    if (_drebezg > 9) {
      _phase = !_phase;
      _drebezg = 0;
      _prev = _curr;
      if (_phase) {
        _counter = _counter + 10;
        _controller->registers.set(_c_address, _counter);
      }
    }
  } else {
    _drebezg = 0;
  }
}

void CWaterCounter::onchange() {
  if (_controller->registers.isChanged(MB_HOLDINGS32 | _c_address)) {
    if (_controller->registers.isInited(MB_HOLDINGS32 | _c_address)) {
      _controller->registers.get(_c_address, _counter);
    }  
  }
}



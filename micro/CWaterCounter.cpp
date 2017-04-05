
#include "CWaterCounter.h"

CWaterCounter::CWaterCounter(CController* controller, uint8_t port):CSensor(controller, 50) {
  _port = port;
  _counter = 255;
  _drebezg = 0;
  _prev = analogRead(_port);
  _phase = _prev;
}

void CWaterCounter::poll() {
  boolean _curr = analogRead(_port);

  #ifndef __NODEBUG__
    Serial.print("_curr = ");
    Serial.println(_curr);
    Serial.print("_prev = ");
    Serial.println(_prev);
    Serial.print("_drebezg = ");
    Serial.println(_drebezg);
  #endif
  
  if (_curr != _prev) {
    _drebezg++;
    if (_drebezg > 9) {
      _phase = !_phase;
      _drebezg = 0;
      _prev = _curr;
      if (_phase) {
        _counter = _counter + 10;
      }
    }
  } else {
    _drebezg = 0;
  }
}



#include <CTimer.h>

CTimer::CTimer(CController* controller, uint16_t address, uint16_t timeout):CTask(controller) {
  _address = address;
  _timeout = timeout;
  _controller->registers.bind(MB_HOLDINGS32, _address);
  _controller->registers.requestInit(MB_HOLDINGS32 | _address);
}

void CTimer::onchange() {
  #ifndef __NODEBUG__
    Serial.print(F("CTimer::onchange"));
  #endif  
  if (_controller->registers.isChanged(MB_HOLDINGS32 | _address)) {
    _controller->registers.get(_address, _time);
    time_t t = *(time_t*)(&_time);
    setTime(t);
#ifndef __NODEBUG__
    Serial.print(day());
    Serial.print("/");
    Serial.print(month());    
    Serial.print("/");
    Serial.print(year());        
    Serial.print(" ");    
    Serial.print(hour());            
    Serial.print(":");                
    Serial.print(minute());           
    Serial.print(":");                
    Serial.println(second());               
#endif    
  }
}



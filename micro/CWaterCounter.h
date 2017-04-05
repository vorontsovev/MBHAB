#ifndef _CWATERCOUNTER_H
#define _CWATERCOUNTER_H

#include "CSensor.h"

const char WaterCounter[] = "CWaterCounter";

class CWaterCounter : public CSensor {
private:
  long _counter;
  uint8_t _port;
  int _drebezg;
  bool _phase;
  bool _prev;
public:
  CWaterCounter(CController* controller, uint8_t port);
  void poll();  
};

#endif


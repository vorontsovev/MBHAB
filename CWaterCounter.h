#ifndef _CWATERCOUNTER_H
#define _CWATERCOUNTER_H

#include "CSensor.h"

const char WaterCounter[] = "CWaterCounter";

class CWaterCounter : public CSensor {
private:
  long _counter;
  int _port;
  int _drebezg;
  bool _phase;
  bool _prev;
public:
  CWaterCounter(CController* controller, String name, int port);
  String getValue(String name);
  void poll();  
};

#endif


#ifndef _CWATERCOUNTER_H
#define _CWATERCOUNTER_H

#include "CSensor.h"

#define _CWATERCOUNTER 0x004

struct CWaterCounterInit {
  uint16_t type;
  uint8_t port;
  uint8_t c_address;
};

class CWaterCounter : public CSensor {
private:
  uint32_t _counter;
  uint8_t _port;
  uint8_t _c_address;
  int _drebezg;
  bool _phase;
  bool _prev;
public:
  CWaterCounter(CController* controller, uint8_t port, uint8_t c_address);
  void poll();  
};

#endif


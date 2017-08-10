#ifndef _CWATCHDOG_H
#define _CWATCHDOG_H

#include <avr/wdt.h>
#include <CController.h>

struct CWatchdogInit {
  uint16_t type;
  uint16_t address;
};

class CWatchdog : public CTask {
private:
  uint16_t _address;
public:
  CWatchdog(CController* controller, uint16_t  address, uint16_t interval);
  void run();
};

#endif

#ifndef _CTIMER_H
#define _CTIMER_H

#include <Time.h>
#include <CController.h>

struct CTimerInit {
  uint16_t type;
  uint16_t address;
  uint16_t timeout;
};

class CTimer : public CTask {
private:
  uint32_t _time;
  uint16_t _address;
  uint16_t _timeout;
  uint32_t _lastpoll;
public:
  CTimer(CController* controller, uint16_t address, uint16_t timeout);
  void onchange();
};

#endif


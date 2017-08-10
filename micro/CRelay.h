#ifndef _CRELAY_H
#define _CRELAY_H

#include <CController.h>

struct CRelayInit {
 uint16_t type;
 uint8_t port;
 uint16_t address;
};

class CRelay : public CTask {
private:
  uint8_t _port;
  uint16_t _address;
  bool _state;
  void handleState();
public:
  CRelay(CController* controller, uint8_t port, uint16_t address);
  void onchange();
  void on();
  void off();
};

#endif

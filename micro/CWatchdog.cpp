#include <CWatchdog.h>

CWatchdog::CWatchdog(CController* controller, uint16_t address, uint16_t interval):CTask(controller) {
  _address = address;
  _controller->registers.bind(MB_COILS, _address);
  _controller->registers.set(_address, true);
  wdt_enable(WDTO_4S);
}

void CWatchdog::run() {
  wdt_reset();
}


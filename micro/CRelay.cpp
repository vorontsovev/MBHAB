#include "CRelay.h"

CRelay::CRelay(CController* controller, uint8_t port, uint16_t address):CTask(controller) {
  _port = port;
  _address = address;
  _state = false;
  _controller->registers.bind(MB_COILS, _address);
  pinMode(_port, OUTPUT);
  off();
}

void CRelay::handleState() {
  digitalWrite(_port, _state);
  _controller->registers.set(_address, _state);
}

void CRelay::on() {
  _state = true;
  handleState();
}

void CRelay::off() {
  _state = false;
  handleState();
}

void CRelay::onchange() {
  if (_controller->registers.isChanged(_address)) {
    _controller->registers.get(_address, _state);
    handleState();
  }
}


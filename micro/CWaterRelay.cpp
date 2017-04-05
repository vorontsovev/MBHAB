#include "CWaterRelay.h"

CWaterRelay::CWaterRelay(CController* controller, uint8_t rs_address, uint8_t cv_port, uint8_t hv_port, uint8_t bv_port, uint8_t bp_port):CTask(controller) {
  #ifndef __NODEBUG__
    Serial.println(F("CREATE CWaterRelay"));
  #endif

  _controller = controller;
  _rs_address = rs_address;
  
  _cv_port = cv_port;
  _hv_port = hv_port;
  _bv_port = bv_port;
  _bp_port = bp_port;

  pinMode(_cv_port, OUTPUT);
  pinMode(_hv_port, OUTPUT);
  pinMode(_bv_port, OUTPUT);
  pinMode(_bp_port, OUTPUT);

  _controller->registers.bind(MB_HOLDINGS, _rs_address);

  setCrash();
  _voltageState = VS_OFF;
}

void CWaterRelay::setRelays(bool cv, bool hv, bool bv, bool bp ) {
  digitalWrite(_cv_port, cv);  
  digitalWrite(_hv_port, hv);
  digitalWrite(_bv_port, bv);
  digitalWrite(_bp_port, bp);
}

void CWaterRelay::setValveState(ValveState state) {
  switch (state) {
case VS_RESERVE_SUPPLY:
    setReserveSupply();
    break;
case VS_CRASH:
    setCrash();
    break;
case VS_MAIN_SUPPLY:
    setMainSupply();
    break;
  }
}

void CWaterRelay::setMainSupply() {
  setRelays(false, false, true, false);
  _controller->registers.set(_rs_address, (uint16_t)2);
  _voltageState = VS_OFF;
}

void CWaterRelay::setReserveSupply() {
  setRelays(false, true, false, true);
  _controller->registers.set(_rs_address, (uint16_t)1);
  _voltageState = VS_ON;
}

void CWaterRelay::setCrash() {
  setRelays(true, true, true, false);
  _controller->registers.set(_rs_address, (uint16_t)0);
  _voltageState = VS_OFF;
}

void CWaterRelay::onchange() {
  if (_controller->registers.isChanged(MB_HOLDINGS | _rs_address)) {
    uint16_t state;
    _controller->registers.get(_rs_address, &state);
    switch (state) {
case 0:
      setCrash();
      break;    
case 1:
      setMainSupply();
      break;
case 2:
      setReserveSupply();
      break;        
    }
    return 0;
  } else {
    return 1;    
  }
}



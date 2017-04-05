#include "CWaterRelay.h"

CWaterRelay::CWaterRelay(CController* controller, String name, uint8_t portColdWater, uint8_t rs_address, uint8_t portHotWater, uint8_t portBoilerWater, uint8_t portBoilerVoltage):CTask(controller, name) {
  _controller = controller;
  _rs_address = rs_address;
  
  _portColdWater = portColdWater;
  _portHotWater = portHotWater;
  _portBoilerWater = portBoilerWater;
  _portBoilerVoltage = portBoilerVoltage;

  pinMode(_portColdWater, OUTPUT);
  digitalWrite(_portColdWater, false);
  pinMode(_portHotWater, OUTPUT);
  digitalWrite(_portHotWater, false);
  pinMode(_portBoilerWater, OUTPUT);
  digitalWrite(_portBoilerWater, false);  
  pinMode(_portBoilerVoltage, OUTPUT);
  digitalWrite(_portBoilerVoltage, false);

  _controller->registers.bind(MB_HOLDINGS, _rs_address);
  
  _voltageState = VS_OFF;
  
  setCrash();

  #ifndef __NODEBUG__
    Serial.println(F("CWaterRelay create done"));
  #endif
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
  digitalWrite(_portBoilerVoltage, false);  
  digitalWrite(_portBoilerWater, true);
  digitalWrite(_portColdWater, false);
  digitalWrite(_portHotWater, false);
  _controller->registers.set(_rs_address, (uint16_t)2);
  _voltageState = VS_OFF;
}

void CWaterRelay::setReserveSupply() {
  digitalWrite(_portColdWater, false);
  digitalWrite(_portHotWater, true);
  digitalWrite(_portBoilerWater, false);
  digitalWrite(_portBoilerVoltage, true);  
  _controller->registers.set(_rs_address, (uint16_t)1);
  _voltageState = VS_ON;
}

void CWaterRelay::setCrash() {
  digitalWrite(_portColdWater, true);
  digitalWrite(_portHotWater, true);
  digitalWrite(_portBoilerWater, true);
  digitalWrite(_portBoilerVoltage, false);  
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



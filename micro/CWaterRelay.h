
#include "CSensor.h"

#ifndef _CWATERRELAY_H
#define _CWATERRELAY_H

const char WaterRelay[] = "CWaterRelay";

enum ValveState {VS_MAIN_SUPPLY, VS_RESERVE_SUPPLY, VS_CRASH};
enum VoltageState {VS_ON, VS_OFF};

class CWaterRelay : public CTask {
private:
  uint8_t _portColdWater;
  uint8_t _portHotWater;
  uint8_t _portBoilerWater;
  uint8_t _portBoilerVoltage;
  ValveState _valveState;
  VoltageState _voltageState;
  uint8_t _rs_address;
protected:  
  void setValveState(ValveState state);
  void setMainSupply();
  void setReserveSupply();
  void setCrash();
  void boilOn();
  void boilOff();
public:
  CWaterRelay(CController* controller, uint8_t rs_address, uint8_t portColdWater, uint8_t portHotWater, uint8_t portBoilerWater, uint8_t portBoilerVoltage);
  void onchange();
};

#endif






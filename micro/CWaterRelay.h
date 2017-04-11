
#include "CSensor.h"

#ifndef _CWATERRELAY_H
#define _CWATERRELAY_H

struct CWaterRelayInit {
  uint8_t type;
  uint8_t rs_address;
  uint8_t cv_port;      // cold water valve port
  uint8_t hv_port;      // hot water valve port
  uint8_t bv_port;      // boiler valve port
  uint8_t bp_port;      // boiler power port
};

enum ValveState {VS_MAIN_SUPPLY, VS_RESERVE_SUPPLY, VS_CRASH};
enum VoltageState {VS_ON, VS_OFF};

class CWaterRelay : public CTask {
private:
  uint8_t _cv_port;
  uint8_t _hv_port;
  uint8_t _bv_port;
  uint8_t _bp_port;
  
  ValveState _valveState;
  VoltageState _voltageState;
  uint8_t _rs_address;
  void setRelays(bool cv, bool hv, bool bv, bool bp);
protected:  
  void setValveState(ValveState state);
  void setMainSupply();
  void setReserveSupply();
  void setCrash();
  void boilOn();
  void boilOff();
public:
  CWaterRelay(CController* controller, uint8_t rs_address, uint8_t cv_port, uint8_t hw_port, uint8_t bw_port, uint8_t bp_port);
  void onchange();
};

#endif






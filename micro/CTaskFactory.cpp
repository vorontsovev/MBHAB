/**
 * Project Untitled
 */


#include "CTaskFactory.h"

/**
 * CTaskFactory implementation
 */


CTaskFactory::CTaskFactory(CController* controller) {
  _controller = controller;
}


CBMP180Sensor* CTaskFactory::createBMP180Sensor(void* initdata) {
  CBMP180Sensor *sensor = new CBMP180Sensor(_controller, ((CBMP180SensorInit*)initdata)->period);
  return sensor;
}

CWaterRelay* CTaskFactory::createWaterRelay(void* initdata) {
  CWaterRelayInit* data;
  data = (CWaterRelayInit*)initdata;
  CWaterRelay* _relay = new CWaterRelay(_controller, data->rs_address, data->cv_port, data->hv_port, data->bv_port, data->bp_port);
  return _relay;
}

CModbusRTUConnector* CTaskFactory::createModbusRTUConnector(void* initdata) {
  CModbusRTUConnectorInit* data;
  data = (CModbusRTUConnectorInit*)initdata;
  CModbusRTUConnector* _modbus = new CModbusRTUConnector(_controller, data->rx, data->tx, data->rate);
  return _modbus;
}

CWaterCounter* CTaskFactory::createWaterCounter(void* initdata) {
  CWaterCounterInit* data;
  data = (CWaterCounterInit*)initdata;
  CWaterCounter* _watercounter = new CWaterCounter(_controller, data->port, data->c_address);
  return _watercounter;
}


CWaterDisplay* CTaskFactory::createWaterDisplay(void* initdata) {
  CWaterDisplayInit* data;
  data = (CWaterDisplayInit*)initdata;
  CWaterDisplay* _waterdisplay = new CWaterDisplay(_controller, data->vs_address, data->cw_address, data->hw_address);
  return _waterdisplay;
}

CWatchdog* CTaskFactory::createWatchdog(void* initdata) {
  CWatchdogInit* data;
  data = (CWatchdogInit*)initdata;
  CWatchdog* wd = new CWatchdog(_controller, data->address, 0);
  return wd;
}

CRelay* CTaskFactory::createRelay(void* initdata) {
  CRelayInit* data;
  data = (CRelayInit*)initdata;
  CRelay* relay = new CRelay(_controller, data->port, data->address);
  return relay;
}



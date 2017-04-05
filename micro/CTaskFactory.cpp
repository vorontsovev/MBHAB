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

/*CWaterCounter* CTaskFactory:: createWaterCounter(String name, JsonObject* root) {
  int port = (*root)["port"];
  CWaterCounter *counter = new CWaterCounter(_controller, name, port);
  return counter;
}

}*/



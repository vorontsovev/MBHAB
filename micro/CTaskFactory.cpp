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


CBMP180Sensor* CTaskFactory::createBMP180Sensor(String name, JsonObject* root) {
  int period = (*root)["period"];
  CBMP180Sensor *sensor = new CBMP180Sensor(_controller, name, period);
  return sensor;
}

CWaterCounter* CTaskFactory:: createWaterCounter(String name, JsonObject* root) {
  int port = (*root)["port"];
  CWaterCounter *counter = new CWaterCounter(_controller, name, port);
  return counter;
}

CWaterRelay* CTaskFactory::createWaterRelay(String name, JsonObject* root) {
  uint8_t _porthw = (*root)["porthw"];
  uint8_t _portcw = (*root)["portcw"];
  uint8_t _portbw = (*root)["portbw"];  
  uint8_t _portbv = (*root)["portbv"];    
  uint8_t _reg_state = (*root)["rs_address"];
  CWaterRelay* _relay = new CWaterRelay(_controller, name, _reg_state, _porthw, _portcw, _portbw, _portbv);
  return _relay;
}

//CEthernetConnector* CTaskFactory::createEthernetConnector(String name, JsonObject* root) {
//  CEthernetConnector* connector = new CEthernetConnector(_controller, name);
//  return connector;
//}


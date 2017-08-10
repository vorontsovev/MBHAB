
/**
 * Library micro
 * CTaskFactory implementation
 */

#include <CTaskFactory.h>

CTaskFactory::CTaskFactory(CController* controller) {
  _controller = controller;
}

#ifdef _CBMP180SENSOR_INC
CBMP180Sensor* CTaskFactory::createBMP180Sensor(void* initdata) {
  CBMP180Sensor *sensor = new CBMP180Sensor(_controller, ((CBMP180SensorInit*)initdata)->period);
  return sensor;
}
#endif // _CBMP180SENSOR_INC

#ifdef _CWATERDISPLAY_INC
CWaterDisplay* CTaskFactory::createWaterDisplay(void* initdata) {
  CWaterDisplayInit* data;
  data = (CWaterDisplayInit*)initdata;
  CWaterDisplay* _waterdisplay = new CWaterDisplay(_controller, data->vs_address, data->bm_address, data->em_address,  data->cw_address, data->hw_address);
  return _waterdisplay;
}
#endif // _CWATERDISPLAY_INC

#ifdef _CWATERRELAY_INC
CWaterRelay* CTaskFactory::createWaterRelay(void* initdata) {
  CWaterRelayInit* data;
  data = (CWaterRelayInit*)initdata;
  CWaterRelay* _relay = new CWaterRelay(_controller, data->rs_address, data->bm_address, data->em_address, data->cv_port, data->hv_port, data->bv_port, data->bp_port);
  return _relay;
}
#endif // _CWATERRELAY_INC

#ifdef _CMODBUSRTUCONNECTOR_INC
CModbusRTUConnector* CTaskFactory::createModbusRTUConnector(void* initdata) {
  CModbusRTUConnectorInit* data;
  data = (CModbusRTUConnectorInit*)initdata;
  CModbusRTUConnector* _modbus = new CModbusRTUConnector(_controller, data->timeout, data->rx, data->tx, data->re, data->de, data->rate);
  return _modbus;
}
#endif // _CMODBUSRTUCONNECTOR_INC

#ifdef _CWATERCOUNTER_INC
CWaterCounter* CTaskFactory::createWaterCounter(void* initdata) {
  CWaterCounterInit* data;
  data = (CWaterCounterInit*)initdata;
  CWaterCounter* _watercounter = new CWaterCounter(_controller, data->port, data->c_address);
  return _watercounter;
}
#endif // _CWATERCOUNTER_INC

#ifdef _CRELAY_INC
CRelay* CTaskFactory::createRelay(void* initdata) {
  CRelayInit* data;
  data = (CRelayInit*)initdata;
  CRelay* relay = new CRelay(_controller, data->port, data->address);
  return relay;
}
#endif // _CRELAY_INC

#ifdef _CTIMER_INC
CTimer* CTaskFactory::createTimer(void* initdata) {
  CTimerInit* data;
  data = (CTimerInit*)initdata;
  CTimer* timer = new CTimer(_controller, data->address, data->timeout);
  return timer;
}
#endif // _CTIMER_INC

#ifdef _CWATERSENSOR_INC
CWaterSensor* CTaskFactory::createWaterSensor(void* initdata) {
  CWaterSensorInit* data;
  data = (CWaterSensorInit*)initdata;
  CWaterSensor* watersensor = new CWaterSensor(_controller, data->i2c_address, data->vs_address, data->sensor_count, data->start_coil);
  return watersensor;
}
#endif // _CWATERSENSOR_INC

#ifdef _CWATCHDOG_INC
CWatchdog* CTaskFactory::createWatchdog(void* initdata) {
  CWatchdogInit* data;
  data = (CWatchdogInit*)initdata;
  CWatchdog* wd = new CWatchdog(_controller, data->address, 0);
  return wd;
}
#endif // _CWATCHDOG_INC


CTask* CTaskFactory::createTask(void* initdata) {
  uint16_t _type = *((uint16_t*)initdata);

  switch (_type) {

#ifdef _CBMP180SENSOR_INC
case _CBMP180SENSOR:
    return this->createBMP180Sensor(initdata);
    break;
#endif // _CBMP180SENSOR_INC

#ifdef _CWATERDISPLAY_INC
case _CWATERDISPLAY:
    return this->createWaterDisplay(initdata);
    break;
#endif // _CWATERDISPLAY_INC   

#ifdef _CWATERRELAY_INC    
case _CWATERRELAY:
    return this->createWaterRelay(initdata);
    break;
#endif // _CWATERRELAY_INC   

#ifdef _CMODBUSRTUCONNECTOR_INC
case _CMODBUSRTUCONNECTOR:
    return this->createModbusRTUConnector(initdata);
    break;
#endif // _CMODBUSRTUCONNECTOR_INC    

#ifdef _CWATERCOUNTER_INC    
case _CWATERCOUNTER:    
    return this->createWaterCounter(initdata);
    break;
#endif // _CWATERCOUNTER_INC

#ifdef _CRELAY_INC    
case _CRELAY:
    return this->createRelay(initdata);  
    break;
#endif // _CRELAY_INC   

#ifdef _CTIMER_INC
case _CTIMER:
    return this->createTimer(initdata);  
    break;
#endif // _CTIMER_INC

#ifdef _CWATERSENSOR_INC    
case _CWATERSENSOR:
    return this->createWaterSensor(initdata);
    break;
#endif // _CWATERSENSOR_INC

#ifdef _CWATCHDOG_INC
case _CWATCHDOG:    
    return this->createWatchdog(initdata);
    break;
#endif // _CWATCHDOG_INC    

  }  
}


/**
 * Project Untitled
 */

#ifndef _CTASKFACTORY_H
#define _CTASKFACTORY_H

#include <init.h>
#include <CClasses.h>


#ifdef _CBMP180SENSOR_INC
  #include <CBMP180Sensor.h>
  class CBMP180Sensor;
#endif // _CBMP180SENSOR_INC

#ifdef _CWATERDISPLAY_INC
  #include <CWaterDisplay.h>
  class CWaterDisplay;
#endif // _CWATERDISPLAY_INC

#ifdef _CWATERRELAY_INC
  #include <CWaterRelay.h>
  class CWaterRelay;
#endif // _CWATERRELAY_INC

#ifdef _CMODBUSRTUCONNECTOR_INC
  #include <CModbusRTUConnector.h>
  class CModbusRTUConnector;
#endif // _CMODBUSRTUCONNECTOR_INC

#ifdef _CWATERCOUNTER_INC
  #include <CWaterCounter.h>
  class CWaterCounter;
#endif // _CWATERCOUNTER_INC

#ifdef _CRELAY_INC  
  #include <CRelay.h>
  class CRelay;
#endif // _CRELAY_INC

#ifdef _CTIMER_INC
  #include <CTimer.h>
  class CTimer;
#endif // CTIMER_INC  

#ifdef _CWATERSENSOR_INC
  #include <CWaterSensor.h>
  class CWaterSensor;
#endif // _CWATERSENSOR_INC 

#ifdef _CWATCHDOG_INC
  #include <CWatchdog.h>
  class CWatchdog;
#endif //_CWATCHDOG_INC  


class CTaskFactory {
private: 
  CController* _controller;  

#ifdef _CBMP180SENSOR_INC 
  CBMP180Sensor* createBMP180Sensor(void* initdata);  
#endif  // _CBMP180SENSOR_INC
  
#ifdef _CWATERDISPLAY_INC
  CWaterDisplay* createWaterDisplay(void* initdata);
#endif // _CWATERDISPLAY_INC 

#ifdef _CWATERRELAY_INC
  CWaterRelay* createWaterRelay(void* initdata);
#endif // _CWATERRELAY_INC 

#ifdef _CMODBUSRTUCONNECTOR_INC
  CModbusRTUConnector* createModbusRTUConnector(void* initdata);
#endif // _CMODBUSRTUCONNECTOR_INC

#ifdef _CWATERCOUNTER_INC
  CWaterCounter* createWaterCounter(void* initdata);
#endif // _CWATERCOUNTER_INC 

#ifdef _CRELAY_INC  
  CRelay* createRelay(void* initdata);
#endif // _CRELAY_INC 

#ifdef _CTIMER_INC
  CTimer* createTimer(void* initdata);
#endif // _CTIMER_INC 

#ifdef _CWATERSENSOR_INC  
  CWaterSensor* createWaterSensor(void* initdata);
#endif // _CWATERSENSOR_INC 

#ifdef _CWATCHDOG_INC
  CWatchdog* createWatchdog(void* initdata);
#endif // _CWATCHDOG_INC  
  
public: 
  CTaskFactory(CController* controller);
  CTask* createTask(void* initdata);
};


#endif // _CTASKFACTORY_H

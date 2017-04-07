/**
 * Project Untitled
 */


#include "CBMP180Sensor.h"
#include "CWaterCounter.h"
#include "CWaterRelay.h"
#include "CModbusRTUConnector.h"
#include "CWaterCounter.h"
#include "CWaterDisplay.h"
#include "CWatchdog.h"

#ifndef _CTASKFACTORY_H
#define _CTASKFACTORY_H

#include <Arduino.h>

class CBMP180Sensor;
class CController;
class CModbusRTUConnector;
class CWaterCounter;
class CWaterDisplay;
class CWatchdog;

class CTaskFactory {
private: 
  CController* _controller;  
public: 
	CTaskFactory(CController* controller);
	
	CBMP180Sensor* createBMP180Sensor(void* initdata);
  CWaterRelay* createWaterRelay(void* initdata);
  CModbusRTUConnector* createModbusRTUConnector(void* initdata);
  CWaterCounter* createWaterCounter(void* initdata);
  CWaterDisplay* createWaterDisplay(void* initdata);
  CWatchdog* createWatchdog(void* initdata);
};

#endif //_CTASKFACTORY_H

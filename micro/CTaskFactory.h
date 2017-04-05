/**
 * Project Untitled
 */


#include "CBMP180Sensor.h"
#include "CWaterCounter.h"
#include "CWaterRelay.h"
//#include "CEthernetConnector.h"

#ifndef _CTASKFACTORY_H
#define _CTASKFACTORY_H

#include <Arduino.h>

class CBMP180Sensor;
//class CEthernetConnector;
//class CWaterCounter;

class CController;

class CTaskFactory {
private: 
  CController* _controller;  
public: 
	
	CTaskFactory(CController* controller);
	
	CBMP180Sensor* createBMP180Sensor(void* initdata);
	//  CWaterCounter* createWaterCounter(String name, JsonObject* root);
//  CWaterRelay* createWaterRelay(String name, JsonObject* root);
//  CEthernetConnector* createEthernetConnector(String name, JsonObject* root);
};

#endif //_CTASKFACTORY_H

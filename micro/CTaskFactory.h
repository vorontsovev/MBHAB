/**
 * Project Untitled
 */


#include "CBMP180Sensor.h"
#include "CWaterCounter.h"
#include "CWaterRelay.h"

#ifndef _CTASKFACTORY_H
#define _CTASKFACTORY_H

#include <Arduino.h>

class CBMP180Sensor;


class CController;

class CTaskFactory {
private: 
  CController* _controller;  
public: 
	
	CTaskFactory(CController* controller);
	
	CBMP180Sensor* createBMP180Sensor(void* initdata);
  CWaterRelay* createWaterRelay(void* initdata);

};

#endif //_CTASKFACTORY_H

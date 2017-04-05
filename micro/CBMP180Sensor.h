


#ifndef _CBMP180SENSOR_H
#define _CBMP180SENSOR_H

#include <Arduino.h>
#include "CSensor.h"
#include "CController.h"
#include <SFE_BMP180.h>
#include <Wire.h>

const char BMP180Sensor[] = "CBMP180Sensor";

class CBMP180Sensor: public CSensor {
private: 
  SFE_BMP180 *_BMP180;
  double _T;
public: 
	
	CBMP180Sensor(CController* controller, String name, int period);
	
	String get(String property);
	
	bool set(String JSON);
	
	bool init(String JSON);
	
	void poll();
	
	String getProperties();
  
  String getValue(String name);
  uint16_t readAI(uint16_t address, long* res);
 
};

#endif //_CBMP180SENSOR_H

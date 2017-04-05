


#ifndef _CBMP180SENSOR_H
#define _CBMP180SENSOR_H

#define _CBMP180SENSOR 0x0001

#include <Arduino.h>
#include "CSensor.h"
#include "CController.h"
#include <SFE_BMP180.h>
#include <Wire.h>

struct CBMP180SensorInit {
  uint16_t type;
  uint16_t period;
};

class CBMP180Sensor: public CSensor {
private: 
  SFE_BMP180 *_BMP180;
  double _T;
public: 
	CBMP180Sensor(CController* controller, uint16_t period);
	void poll();
};

#endif //_CBMP180SENSOR_H

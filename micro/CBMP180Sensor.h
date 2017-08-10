
#ifndef _CBMP180SENSOR_H
#define _CBMP180SENSOR_H

#include <stdint.h>
#include <SFE_BMP180.h>
#include <CSensor.h>

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

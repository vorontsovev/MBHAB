#ifndef _CWATERSENSOR_H
#define _CWATERSENSOR_H

#include <PCF8574.h>
#include <CController.h>

struct CWaterSensorInit {
  uint16_t type;
  uint8_t i2c_address;
  uint8_t vs_address;
  uint8_t sensor_count;
  uint8_t start_coil;
};

class CWaterSensor : public CSensor {
private:
  PCF8574* _expander;
  uint8_t _i2c_address;
  uint8_t _vs_address;
  uint8_t _sensor_count;
  uint8_t _start_coil;

public:
  CWaterSensor(CController* controller, uint8_t i2c_address, uint8_t vs_address, uint8_t sensor_count, uint8_t start_coil);
  void onchange();
  void poll();
};

#endif

#include <CWaterSensor.h>


CWaterSensor::CWaterSensor(CController* controller, uint8_t i2c_address, uint8_t vs_address, uint8_t sensor_count, uint8_t start_coil):CSensor(controller, 1000) {

  #ifndef __NODEBUG__
      Serial.println(F("CREATE CWaterSensor"));
  #endif
  _vs_address = vs_address;
  _sensor_count = sensor_count;
  _start_coil = start_coil;
  _expander = new PCF8574();
  _expander->begin(0x38);

  for (uint8_t i=0; i < sensor_count; i++) {
    _expander->pinMode(0, INPUT);
    _controller->registers.bind(MB_COILS, _start_coil+i);
    _controller->registers.set(_start_coil+i, false);
  }

}

void CWaterSensor::poll() {
  #ifndef __NODEBUG__
    Serial.println(F("CWaterSensor poll"));
  #endif
  for (uint8_t i=0; i<_sensor_count;i++) {
    Serial.println(_expander->digitalRead(i));
    if (LOW == _expander->digitalRead(i)) {
      uint16_t _state = 0;
      _controller->registers.set(_start_coil+i, true);
      _controller->registers.set(_vs_address, _state);
    }
  }
}

void CWaterSensor::onchange() {
  if (_controller->registers.isChanged(MB_HOLDINGS | _vs_address)) {
    #ifndef __NODEBUG__
        Serial.println(F("RelayState Change"));
    #endif
    uint16_t _state;
    _controller->registers.get(_vs_address, _state);
    if (_state != 0) {
      for (uint8_t i=0; i<_sensor_count;i++) {      
        _controller->registers.set(_start_coil+i, false);         
      }
    }
  }
}


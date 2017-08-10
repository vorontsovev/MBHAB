#include <CBMP180Sensor.h>

CBMP180Sensor::CBMP180Sensor(CController* controller, uint16_t period):CSensor(controller, period) {

  #ifndef __NODEBUG__
      Serial.println(F("CREATE CBMP180Sensor"));
      Serial.print(F("period="));
      Serial.println(period);
  #endif
  _BMP180 = new SFE_BMP180();

  _BMP180->begin();
}

void CBMP180Sensor::poll() {
  #ifndef __NODEBUG__
    Serial.println(F("CBMP180Sensor poll"));
  #endif
  
  double temp;
  char status = _BMP180->startTemperature();
  if (status != 0)
  {
    delay(status);

    status = _BMP180->getTemperature(temp);
    if (status != 0)
    {
      if (_T != temp) {
        _T = temp;
        _poll = millis();
      }
    }

    #ifndef __NODEBUG__
      Serial.print("Temperature=");
      Serial.println(_T);
    #endif
  }
}





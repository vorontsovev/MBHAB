

#include "CBMP180Sensor.h"


CBMP180Sensor::CBMP180Sensor(CController* controller, String name, int period):CSensor(controller, name, period) {
  Serial.println(F("CBMP180Sensor"));  

  #ifndef __NODEBUG__
      Serial.print(F("name="));
      Serial.println(name);
      Serial.print(F("period="));
      Serial.println(period);
  #endif
  _BMP180 = new SFE_BMP180();

  _BMP180->begin();
}


String CBMP180Sensor::get(String property) {
    return "";
}

bool CBMP180Sensor::set(String JSON) {
    return false;
}

bool CBMP180Sensor::init(String JSON) {
    return false;
}

void CBMP180Sensor::poll() {
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


String CBMP180Sensor::getProperties() {
    return "";
}

String CBMP180Sensor::getValue(String name) {
  if (name.equals("T")) {
    return String(_T);
  }
}

uint16_t CBMP180Sensor::readAI(uint16_t address, long* res) {
  if (address == 0x0000) {
    *res = round(_T * 100);
#ifndef __NODEBUG__
    Serial.print("t = ");
    Serial.println(round(_T * 100));
#endif    
    return 0;
  } else return 1;
}



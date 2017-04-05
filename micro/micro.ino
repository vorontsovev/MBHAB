//#define __NODEBUG__

#include "CController.h"
#include "CDisplay.h"
#include "CModbusRegisters.h"


CController *controller = new CController();

void setup() {

CBMP180SensorInit         bmp180init = {.type=_CBMP180SENSOR, .period=5000};
CWaterRelayInit           wrInit = {.type=_CWATERRELAY, .rs_address=0, .cv_port=11, .hv_port=10, .bv_port=9, .bp_port=8};
CModbusRTUConnectorInit   mbInit = {.type=_CMODBUSRTUCONNECTOR, .rx=2, .tx=3, .rate=2400};
  
  #ifndef __NODEBUG__
    Serial.begin(115200);
    Serial.println(F("DEBUG MODE ON"));
  #endif

  controller->createTask(&bmp180init);
  controller->createTask(&wrInit);
  controller->createTask(&mbInit);
}

void loop() {
  // put your main code here, to run repeatedly:
  controller->run();
}

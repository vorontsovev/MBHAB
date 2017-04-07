//#define __NODEBUG__

#include "CController.h"

CController *controller = new CController();

void setup() {

//CBMP180SensorInit         bmp180init = {.type=_CBMP180SENSOR, .period=5000};
CWaterRelayInit           wrInit = {.type=_CWATERRELAY, .rs_address=0, .cv_port=11, .hv_port=10, .bv_port=9, .bp_port=8};
CModbusRTUConnectorInit   mbInit = {.type=_CMODBUSRTUCONNECTOR, .rx=2, .tx=3, .rate=2400};
CWaterCounterInit         wcInit1 = {.type=_CWATERCOUNTER, .port=1, .c_address=1};
CWaterCounterInit         wcInit2 = {.type=_CWATERCOUNTER, .port=2, .c_address=3};
CWaterDisplayInit         disInit = {.type=_CWATERDISPLAY, .vs_address=0, .cw_address=1, .hw_address=3};
CWatchdogInit             wdInit = {.type= _CWATCHDOG, .address=0};
  
  #ifndef __NODEBUG__
    Serial.begin(115200);
    Serial.println(F("DEBUG MODE ON"));
  #endif

  controller->createTask(&wdInit);
  controller->createTask(&wrInit);
  controller->createTask(&wcInit1);
  controller->createTask(&wcInit2);
  controller->createTask(&disInit);  
  controller->createTask(&mbInit);  
}

void loop() {
  // put your main code here, to run repeatedly:
  controller->run();
}

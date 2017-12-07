#include <micro.h>


CController *controller = new CController();

void setup() {

  //CBMP180SensorInit         bmp180init = {.type = _CBMP180SENSOR, .period = 5000};
  CWaterRelayInit           wrInit = {.type=_CWATERRELAY, .rs_address=0, .bm_address=1, .em_address=2, .cv_port=11, .hv_port=10, .bv_port=9, .bp_port=8};
  CModbusRTUConnectorInit   mbInit = {.type=_CMODBUSRTUCONNECTOR, .id=5, .timeout=5000, .rx=2, .tx=3, .re=6, .de=6, .rate=9600};
  CWaterCounterInit         wcInit1 = {.type=_CWATERCOUNTER, .port=1, .c_address=18};
  CWaterCounterInit         wcInit2 = {.type=_CWATERCOUNTER, .port=2, .c_address=20};
  CWaterDisplayInit         disInit = {.type=_CWATERDISPLAY, .vs_address=0, .bm_address=1, .em_address=2, .cw_address=18, .hw_address=20};
  CWatchdogInit             wdInit = {.type=_CWATCHDOG, .address=0};
  CTimerInit                timer = {.type=_CTIMER, .address=16, .timeout=1500};
  CWaterSensorInit          wsInit = {.type=_CWATERSENSOR, .i2c_address=0x38, .vs_address=0, .sensor_count=2, .start_coil = 8};
  CRelayInit                erToilet = {.type=6, .port=12, .address=20}; 
  CRelayInit                erBathRoom = {.type=6, .port=13, .address=21}; 
  //CRelayInit                erBathRoom = {.type=6, .port=13, .address=21}; 


#ifndef __NODEBUG__
  Serial.begin(115200);
  Serial.println(F("DEBUG MODE ON"));
#endif

//  controller->createTask(&bmp180init);
    controller->createTask(&wdInit);
    controller->createTask(&timer);
    controller->createTask(&wrInit);
    controller->createTask(&wcInit1);
    controller->createTask(&wcInit2);
//    controller->createTask(&disInit);
    controller->createTask(&wsInit);
    controller->createTask(&erToilet);
    controller->createTask(&erBathRoom);
    controller->createTask(&mbInit);
}

void loop() {
  // put your main code here, to run repeatedly:
  controller->run();
}


//#define __NODEBUG__

#include "CController.h"
#include "CDisplay.h"
#include "CModbusRegisters.h"

const char config[] = "{""type"":""CBMP180Sensor"",""name"":""TEMP1"",""period"":5000}";
//const char config2[] = "{""type"":""CEthernetConnector"",""name"":""ETH0""}";
//const char config3[] = "{""type"":""CWaterCounter"",""name"":""COLD"",""port"":0}";
const char config4[] = "{""type"":""CWaterRelay"",""name"":""WR"",""rs_address"":0,""porthw"":11,""portcw"":10,""portbw"":9,""portbv"":8}";

CController *controller = new CController(2, 3, 2400);

void setup() {
  #ifndef __NODEBUG__
    Serial.begin(115200);
    Serial.println(F("DEBUG MODE ON"));
  #endif

//  CDisplay *lcd = new CDisplay(controller);  
  controller->createTask(config);
  controller->createTask(config4);

//  controller->createTask(config3);
//  lcd->attach("WR");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  controller->run();
}

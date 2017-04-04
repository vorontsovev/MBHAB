#include <Arduino.h>

struct CI_CWATERRELAY {
  uint8_t cw_port;
  uint8_t hw_port;
  uint8_t bw_port;
  uint8_t bv_port;
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(2400);
  CI_CWATERRELAY init_water_relay = {.cw_port = 1, .hw_port = 2, .bw_port = 3, .bv_port = 4};
  Serial.println(sizeof(init));
}

void loop() {
  // put your main code here, to run repeatedly:

}

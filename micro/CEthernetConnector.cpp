/**
 * Project Untitled
 */


#include "CEthernetConnector.h"

/**
 * CEthernetConnector implementation
 */


CEthernetConnector::CEthernetConnector(CController* controller) : CTask(controller) {
  _server = new EthernetServer(80);

  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  IPAddress ip(192,168,0,6);
  
  Ethernet.begin(mac, ip);

  _server->begin();
}

void CEthernetConnector::run() {
  EthernetClient client = _server->available();
  if (client) {
    Serial.println(F("new client"));
    client.stop();
  }
}


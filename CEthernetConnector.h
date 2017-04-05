/**
 * Project Untitled
 */


#ifndef _CETHERNETCONNECTOR_H
#define _CETHERNETCONNECTOR_H

#include "CTask.h"
#include <UIPEthernet.h>


const char EthernetConnector[] = "CEthernetConnector";

class CEthernetConnector : public CTask {
private:
  EthernetServer* _server;  
public: 
  CEthernetConnector(CController* controller, String name);
  void run();
};

#endif //_CETHERNETCONNECTOR_H

/**
 * Project Untitled
 */


#include "CTask.h"
#include "CJSONGate.h"
#include "CController.h"

#ifndef _CSENSOR_H
#define _CSENSOR_H

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <list>

class CSensor: public CTask, public CJSONGate {
private: 
  uint16_t _period;
  uint32_t _counter;
protected:  
  long _poll;
public: 
	CSensor(CController* controller, uint16_t period);

	uint16_t getPeriod();
	void run();
	virtual void poll();
	
  uint32_t getLastPoll();
};

#endif //_CSENSOR_H

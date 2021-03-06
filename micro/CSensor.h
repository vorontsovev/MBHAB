/**
 * Project Untitled
 */


#ifndef _CSENSOR_H
#define _CSENSOR_H

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <bitset>
#include <CTask.h>


class CSensor: public CTask {
private: 
  uint16_t _period;
  uint32_t _counter;
protected:  
  uint32_t _poll;
public: 
	CSensor(CController* controller, uint16_t period);

	uint16_t getPeriod();
	void run();
	virtual void poll();
	
  uint32_t getLastPoll();
};

#endif //_CSENSOR_H

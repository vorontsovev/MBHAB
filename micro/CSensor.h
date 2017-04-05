/**
 * Project Untitled
 */


#include "CTask.h"
#include "CJSONGate.h"
#include "CController.h"

#ifndef _CSENSOR_H
#define _CSENSOR_H

#include <Arduino.h>
#include "CHandleEvent.h"
#include <StandardCplusplus.h>
#include <list>

class CSensor: public CTask, public CJSONGate {
private: 
  int _period;
  long _counter;
  std::list <CHandleEvent*> _handleEvents;
  std::list <CHandleEvent*>::iterator _it;  
protected:  
  long _poll;
public: 
	CSensor(CController* controller, String name, int period);
  void registerHandleEvent(CHandleEvent* handleEvent);
	
	int getPeriod();
	
	void run();
  void handleEvents();
	
	virtual void poll();
	
  long getLastPoll();

  virtual String getValue(String name);
};

#endif //_CSENSOR_H

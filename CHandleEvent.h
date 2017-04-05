
#include "CController.h"

#ifndef _CHANDLEEVENT_H
#define _CHANDLEEVENT_H

#include "CSensor.h"

class CSensor;

class CHandleEvent {
private:
  long _lasthandle;
  CController* _controller;
public:
  CHandleEvent(CController* controller);
  virtual void handleEvent(CSensor* sensor);
  void attach(String name);
};

#endif //_CHANLEEVENT_H

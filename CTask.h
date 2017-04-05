/**
 * Project Untitled
 */

#include "CController.h"

#ifndef _CTASK_H
#define _CTASK_H


class CController;

class CTask {
private: 
  bool _active;
  String _name;
protected: 
  CController *_controller;
public: 
	CTask(CController *controller, String name);
	
	virtual void run();
  virtual void onchange();
	
	bool getActive();
	
	void setActive(bool active);
  String getName();
  virtual uint16_t readDO(uint16_t address, uint8_t* res);
  virtual uint16_t readAO(uint16_t address, uint16_t* res);  
  virtual uint16_t readAI(uint16_t address, uint16_t* res);
  virtual uint16_t readAO32(uint16_t address, long* res);    
  virtual uint16_t writeAO(uint16_t address, uint16_t reg);    
  virtual uint16_t writeAO32(uint16_t address, uint32_t reg);      
};

#endif //_CTASK_H

/**
 * Project Untitled
 */

#ifndef _CTASK_H
#define _CTASK_H

class CController;

class CTask {
private: 
  bool _active;
protected: 
  CController *_controller;
public: 
	CTask(CController *controller);
	
	virtual void run();
    virtual void onchange();
	
	bool getActive();
	
	void setActive(bool active);
};

#endif //_CTASK_H

/**
 * Project Untitled
 */

#ifndef _CTASKMANAGER_H
#define _CTASKMANAGER_H

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <list>
#include "CTask.h"

class CTaskManager {
private:
    uint8_t _counter;
    std::list <CTask*> _tasks;
    std::list <CTask*>::iterator _it;
public: 
	
	CTaskManager();
	
	void addTask(CTask *task);
	
	void deleteTask(CTask *task);

  void run();
  void onchange();

};

#endif //_CTASKMANAGER_H

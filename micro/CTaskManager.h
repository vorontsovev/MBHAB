/**
 * Project Untitled
 */


#include "CTask.h"
#include <StandardCplusplus.h>
#include <list>

#ifndef _CTASKMANAGER_H
#define _CTASKMANAGER_H

class CTaskManager {
private:
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

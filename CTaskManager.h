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
  
  CTask* getTaskByName(String name);

  uint16_t readDO(uint16_t address, uint8_t* reg);
  uint16_t readAI(uint16_t address, uint16_t* reg);  
  uint16_t readAO(uint16_t address, uint16_t* reg);
  uint16_t readAO32(uint16_t address, uint32_t* reg);    
  uint16_t writeAO(uint16_t address, uint16_t reg);
  uint16_t writeAO32(uint16_t address, uint32_t reg);  
};

#endif //_CTASKMANAGER_H

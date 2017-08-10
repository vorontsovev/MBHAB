#include <CTaskManager.h>

CTaskManager::CTaskManager() {
  _counter = 0;
}

void CTaskManager::addTask(CTask *task) {
  #ifndef __NODEBUG__
    Serial.print("CTaskManager.addTask()=");
    Serial.println(_counter);    
  #endif
  _counter++;
  _tasks.push_back(task);
}

void CTaskManager::deleteTask(CTask *task) {

}

void CTaskManager::run() {
  _it = _tasks.begin();
  
  while (_it != _tasks.end()) {
    (*_it)->run();
    _it++;
  }
}

void CTaskManager::onchange() {
  _it = _tasks.begin();
  int i = 0;

  while (_it != _tasks.end()) {
    #ifndef __NODEBUG__
      Serial.print("TaskManager.onchange it=");
      Serial.println(i);
      i++;
    #endif
    (*_it)->onchange();
    _it++;
  }
}



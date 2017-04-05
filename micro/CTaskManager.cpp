#include "CTaskManager.h"


CTaskManager::CTaskManager() {

}

void CTaskManager::addTask(CTask *task) {
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

  while (_it != _tasks.end()) {
    (*_it)->onchange();
    _it++;
  }
}



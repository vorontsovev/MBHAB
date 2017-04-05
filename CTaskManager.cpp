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

CTask* CTaskManager::getTaskByName(String name) {
  _it = _tasks.begin();
  
  while (_it != _tasks.end()) {
    if ((*_it)->getName() == name) return (*_it);
    delay(1);
    _it++;
  }

  #ifndef __NODEBUG__
    Serial.print("Task ");
    Serial.print(name);
    Serial.println(" not found");  
  #endif

  return 0;
  
}

uint16_t CTaskManager::readDO(uint16_t _address, uint8_t* res) {
  _it = _tasks.begin();
  
  while (_it != _tasks.end()) {
    if ((*_it)->readDO(_address, res)) return 0;
    delay(1);
    _it++;
  } 
  return 2; 
}

uint16_t CTaskManager::readAO(uint16_t _address, uint16_t* res) {
  _it = _tasks.begin();
  
  while (_it != _tasks.end()) {
    if (!(*_it)->readAO(_address, res)) return 0;
    delay(1);
    _it++;
  } 
  return 2; 
}

uint16_t CTaskManager::readAI(uint16_t address, uint16_t* reg) {
  _it = _tasks.begin();
  
  while (_it != _tasks.end()) {
    if (!(*_it)->readAI(address, reg)) return 0;
    delay(1);
    _it++;
  } 
  return 2; 
}

uint16_t CTaskManager::readAO32(uint16_t address, uint32_t* reg) {
  _it = _tasks.begin();
  
  while (_it != _tasks.end()) {
    if (!(*_it)->readAO32(address, reg)) return 0;
    delay(1);
    _it++;
  } 
  return 2; 
}

uint16_t CTaskManager::writeAO(uint16_t address, uint16_t reg) {
  _it = _tasks.begin();
  
  while (_it != _tasks.end()) {
    if (!(*_it)->writeAO(address, reg)) return 0;
    delay(1);
    _it++;
  } 
  return 2; 
}

uint16_t CTaskManager::writeAO32(uint16_t address, uint32_t reg) {
  _it = _tasks.begin();
  
  while (_it != _tasks.end()) {
    if (!(*_it)->writeAO32(address, reg)) return 0;
    delay(1);
    _it++;
  } 
  return 2; 
}


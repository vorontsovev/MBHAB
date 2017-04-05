/**
 * Project Untitled
 */


#include "CTask.h"

/**
 * CTask implementation
 */


/**
 * @param controller
 */
CTask::CTask(CController* controller, String name) {
	_active = false;
  _name = name;
	_controller = controller;
}

void CTask::run() {

}

void CTask::onchange() {

}


/**
 * @return bool
 */
bool CTask::getActive() {
    return _active;
}

/**
 * @param active
 */
void CTask::setActive(bool active) {
	_active = active;
}

String CTask::getName() {
  return _name;
}

uint16_t CTask::readDO(uint16_t address, uint8_t* reg) {
  *reg = 0;
  return 1;
}

uint16_t CTask::readAO(uint16_t address, uint16_t* reg) {
  *reg = 0;
  return 1;
}

uint16_t CTask::readAI(uint16_t address, uint16_t* reg) {
  *reg = 0;
  return 1;
}

uint16_t CTask::readAO32(uint16_t address, long* reg) {
  *reg = 0;
  return 1;
}

uint16_t CTask::writeAO(uint16_t address, uint16_t reg) {
  return 1;
}

uint16_t CTask::writeAO32(uint16_t address, uint32_t reg) {
  return 1;
}


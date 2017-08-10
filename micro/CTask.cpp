#include "CTask.h"

/**
 * CTask implementation
 */

/**
 * @param controller
 */
CTask::CTask(CController* controller) {
	_active = false;
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


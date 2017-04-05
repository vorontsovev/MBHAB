/**
 * Project Untitled
 */


#include "CMonitor.h"

/**
 * CMonitor implementation
 */


/**
 * @param controller
 * @param connector
 */
CMonitor::CMonitor(CController *controller, String name, CConnector *connector):CTask(controller, name),CJSONGate() {

}

/**
 * Project Untitled
 */


#ifndef _CMONITOR_H
#define _CMONITOR_H

#include "CTask.h"
#include "CConnector.h"
#include "CJSONGate.h"


class CConnector;
class CTask;
class CJSONGate;

class CMonitor: public CTask, public CJSONGate {
public: 
	
	/**
	 * @param controller
	 * @param connector
	 */
	CMonitor(CController *controller, String name, CConnector *connector);
private: 
	CConnector *_connector;
};

#endif //_CMONITOR_H

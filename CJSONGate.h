/**
 * Project Untitled
 */


#ifndef _CJSONGATE_H
#define _CJSONGATE_H

class CJSONGate {
public: 
	
	CJSONGate();
	
	virtual String get();
	
	virtual bool set(String JSON);
	
	virtual bool init(String JSON);
	
	virtual String getProperties();
};

#endif //_CJSONGATE_H

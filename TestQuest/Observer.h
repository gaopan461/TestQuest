#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer
{
public:
	virtual int OnEvent(int eid,void* param) = 0;
};

#endif//_OBSERVER_H_
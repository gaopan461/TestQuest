#ifndef _OBSERVABLE_H_
#define _OBSERVABLE_H_

#include <map>
#include <vector>
#include "Observer.h"

class Observable
{
public:
	Observable();
	~Observable();
public:
	int AddObserver(int eid,Observer* observer);
	int DelObserver(int eid,Observer* observer);
public:
	int InjectEvent(int eid,void* param);
protected:
	typedef std::map<int,std::vector<Observer*>> CollectionObserversT;
private:
	CollectionObserversT m_mapObservers;
};
#endif//_OBSERVABLE_H_
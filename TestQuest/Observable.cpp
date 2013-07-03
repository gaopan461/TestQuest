#include "Observable.h"
#include <assert.h>

Observable::Observable()
{
	m_mapObservers.clear();
}

Observable::~Observable()
{
	m_mapObservers.clear();
}

int Observable::AddObserver(int eid,Observer* observer)
{
	assert(observer);
	m_mapObservers[eid].push_back(observer);
	return 0;
}

int Observable::DelObserver(int eid,Observer* observer)
{
	assert(observer);

	CollectionObserversT::iterator iterMap = m_mapObservers.find(eid);
	if(iterMap == m_mapObservers.end())
		return -1;

	std::vector<Observer*>& vtObservers = iterMap->second;
	for(std::vector<Observer*>::iterator iter = vtObservers.begin(); iter != vtObservers.end();)
	{
		if(*iter == observer)
			iter = vtObservers.erase(iter);
		else
			++iter;
	}

	return 0;
}

int Observable::InjectEvent(int eid,void* param)
{
	CollectionObserversT::iterator iterMap = m_mapObservers.find(eid);
	if(iterMap == m_mapObservers.end())
		return -1;

	std::vector<Observer*>& vtObservers = iterMap->second;
	for(std::vector<Observer*>::iterator iter = vtObservers.begin(); iter != vtObservers.end();)
	{
		int ret = (*iter)->OnEvent(eid,param);
		if(ret > 0)
			iter = vtObservers.erase(iter);
		else
			++iter;
	}

	return 0;
}
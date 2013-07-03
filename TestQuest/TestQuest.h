#ifndef _TEST_QUEST_H_
#define _TEST_QUEST_H_

#include "Observer.h"
#include <map>
#include <vector>

enum ETestQuestGoalID
{
	TEST_QUEST_GOAL_ID_1,
	TEST_QUEST_GOAL_ID_2,
};

struct STestQuestGoal
{
	int nGoalID;
	int nObserverCount;
	int nCurrentCount;

	STestQuestGoal(int gid,int count)
		: nGoalID(gid)
		, nObserverCount(count)
		, nCurrentCount(0)
	{}

	bool IsAchieved()
	{
		return nCurrentCount >= nObserverCount;
	}

	void Reset()
	{
		nCurrentCount = 0;
	}

	void Finish()
	{
		nCurrentCount = nObserverCount;
	}
};

enum ETestQuestState
{
	TEST_QUEST_STATE_CANACCEPT,
	TEST_QUEST_STATE_UNDERWAY,
	TEST_QUEST_STATE_FINISHED,
	TEST_QUEST_STATE_SUBMITED,
};

class TestQuestGoalMgr;

class TestQuest : public Observer
{
protected:
	typedef std::map<int,STestQuestGoal*> CollectionGoalsMT;
	typedef std::vector<STestQuestGoal> CollectionGoalsVT;
public:
	TestQuest(int nId,CollectionGoalsVT& vtGoals,TestQuestGoalMgr* pGoalMgr);
	~TestQuest();
public:
	virtual int OnEvent(int gid,void* param);
public:
	int InitialAllGoals(CollectionGoalsVT& vtGoals);
	int SetAllGoals();
	int ClearAllGoals();
	int FinishAllGoals();
public:
	int Accept();
	int Giveup();
	int Finish();
	int Submit();
private:
	void Print();
private:
	int OnGoalAchieved();
private:
	CollectionGoalsMT m_mapGoals;
	CollectionGoalsVT m_vtGoals;
	TestQuestGoalMgr* m_pGoalMgr;
	int m_nID;
	int m_nState;
};

#endif//_TEST_QUEST_H_
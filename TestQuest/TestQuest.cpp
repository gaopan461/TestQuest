#include "TestQuest.h"
#include "TestQuestGoalMgr.h"
#include <iostream>
#include <assert.h>

TestQuest::TestQuest(int nId,CollectionGoalsVT& vtGoals,TestQuestGoalMgr* pGoalMgr)
: m_nID(nId)
, m_pGoalMgr(pGoalMgr)
, m_nState(TEST_QUEST_STATE_CANACCEPT)
{
	m_mapGoals.clear();
	InitialAllGoals(vtGoals);
}

TestQuest::~TestQuest()
{
	m_mapGoals.clear();
}

int TestQuest::InitialAllGoals(CollectionGoalsVT& vtGoals)
{
	for(CollectionGoalsVT::iterator it = vtGoals.begin(),ed = vtGoals.end(); it != ed; ++it)
		m_vtGoals.push_back(*it);

	return 0;
}

int TestQuest::SetAllGoals()
{
	ClearAllGoals();

	for(CollectionGoalsVT::iterator it = m_vtGoals.begin(),ed = m_vtGoals.end(); it != ed; ++it)
	{
		m_mapGoals.insert(std::make_pair(it->nGoalID,&(*it)));
		m_pGoalMgr->AddObserver(it->nGoalID,this);
	}
	return 0;
}

int TestQuest::ClearAllGoals()
{
	for(CollectionGoalsMT::iterator it = m_mapGoals.begin(),ed = m_mapGoals.end(); it != ed; ++it)
	{
		STestQuestGoal* pGoal = it->second;
		assert(pGoal);

		m_pGoalMgr->DelObserver(pGoal->nGoalID,this);
	}

	m_mapGoals.clear();

	for(CollectionGoalsVT::iterator it = m_vtGoals.begin(),ed = m_vtGoals.end(); it != ed; ++it)
	{
		it->Reset();
	}

	return 0;
}

int TestQuest::FinishAllGoals()
{
	for(CollectionGoalsMT::iterator it = m_mapGoals.begin(),ed = m_mapGoals.end(); it != ed; ++it)
	{
		STestQuestGoal* pGoal = it->second;
		assert(pGoal);

		m_pGoalMgr->DelObserver(pGoal->nGoalID,this);
	}

	m_mapGoals.clear();

	for(CollectionGoalsVT::iterator it = m_vtGoals.begin(),ed = m_vtGoals.end(); it != ed; ++it)
	{
		it->Finish();
	}

	return 0;
}

int TestQuest::Accept()
{
	if(m_nState != TEST_QUEST_STATE_CANACCEPT)
		return -1;

	SetAllGoals();

	m_nState = TEST_QUEST_STATE_UNDERWAY;

	Print();
	return 0;
}

int TestQuest::Giveup()
{
	if(m_nState != TEST_QUEST_STATE_UNDERWAY && m_nState != TEST_QUEST_STATE_FINISHED)
		return -1;

	ClearAllGoals();

	m_nState = TEST_QUEST_STATE_CANACCEPT;

	Print();
	return 0;
}

int TestQuest::Finish()
{
	if(m_nState != TEST_QUEST_STATE_UNDERWAY && m_nState != TEST_QUEST_STATE_FINISHED)
		return -1;

	if(m_nState == TEST_QUEST_STATE_FINISHED)
		return 0;

	FinishAllGoals();

	m_nState = TEST_QUEST_STATE_FINISHED;

	Print();
	return 0;
}

int TestQuest::Submit()
{
	if(m_nState != TEST_QUEST_STATE_FINISHED)
		return -1;

	ClearAllGoals();

	m_nState = TEST_QUEST_STATE_SUBMITED;

	Print();
	return 0;
}

int TestQuest::OnEvent(int gid,void* param)
{
	CollectionGoalsMT::iterator iter = m_mapGoals.find(gid);
	if(iter == m_mapGoals.end())
		return -1;

	STestQuestGoal* pGoal = iter->second;

	pGoal->nCurrentCount++;

	if(pGoal->IsAchieved())
	{
		m_mapGoals.erase(iter);

		if(m_mapGoals.empty())
			OnGoalAchieved();
		else
			Print();

		return 1;
	}

	Print();
	return 0;
}

int TestQuest::OnGoalAchieved()
{
	m_nState = TEST_QUEST_STATE_FINISHED;
	std::cout << "[Quest:" << m_nID << "]" << " Achieved" << std::endl;
	Print();
	return 0;
}

void TestQuest::Print()
{
	std::cout << std::endl;
	std::cout << "[Quest:" << m_nID << "]" << "\n\t"
		<< "State:" << m_nState << "\n\t";

	for(CollectionGoalsVT::iterator it = m_vtGoals.begin(),ed = m_vtGoals.end(); it != ed; ++it)
	{
		std::cout << "gid:" << it->nGoalID << ",status:" << it->nCurrentCount << "/" << it->nObserverCount << "\n\t";
	}

	std::cout << std::endl;
}

#include "TestQuest.h"
#include "TestQuestGoalMgr.h"
#include <iostream>

int main()
{
	TestQuestGoalMgr* pGoalMgr = new TestQuestGoalMgr();

	std::vector<STestQuestGoal> vtGoals1;
	vtGoals1.push_back(STestQuestGoal(TEST_QUEST_GOAL_ID_1,2));
	vtGoals1.push_back(STestQuestGoal(TEST_QUEST_GOAL_ID_2,3));
	TestQuest* pQuest1 = new TestQuest(1,vtGoals1,pGoalMgr);

	std::vector<STestQuestGoal> vtGoals2;
	vtGoals2.push_back(STestQuestGoal(TEST_QUEST_GOAL_ID_2,2));
	TestQuest* pQuest2 = new TestQuest(2,vtGoals2,pGoalMgr);

	pQuest1->Accept();
	pQuest2->Accept();

	char cmd;
	while(std::cin >> cmd)
	{
		bool quit = false;
		switch(cmd)
		{
		case 'q':
		case 'Q':
			quit = true;
			break;
		case '1':
			pGoalMgr->InjectEvent(TEST_QUEST_GOAL_ID_1,NULL);
			break;
		case '2':
			pGoalMgr->InjectEvent(TEST_QUEST_GOAL_ID_2,NULL);
			break;
		}

		if (quit)
			break;
	}

	delete pQuest1;
	delete pQuest2;
	delete pGoalMgr;
	return 0;
}
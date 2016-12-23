#include "Archives.h"

Archives* Archives::m_pArchives = NULL;

Archives::Archives()
{
	getArchives();
}

Archives* Archives::sharedArchives()
{
	if(!m_pArchives)
	{
		m_pArchives = new Archives();
	}
	CCAssert(m_pArchives,"创建游戏存档类失败");
	return m_pArchives;
}

//读取游戏存档
void Archives::getArchives()
{
	Hero::sharedHero();//读取玩家档
	CardTeam::sharedCardTeam();//读取卡牌团队的档
	GuanQiaState::sharedGuanQiaState();//读取关卡
}
//设置游戏存档
void Archives::setArchives()
{
	Hero::sharedHero()->setHero_property();//存取玩家档
	CardTeam::sharedCardTeam()->setCardTeamPor();//存卡牌团队的档
	GuanQiaState::sharedGuanQiaState()->setGuanQiaState();//存关卡
}



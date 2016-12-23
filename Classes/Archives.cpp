#include "Archives.h"

Archives* Archives::m_pArchives = NULL;

Archives::Archives()
{

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

bool Archives::isExist()
{
	return CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml");
}
//读取游戏存档
void Archives::getHero_Property(Hero &var)
{
	var.setName_(getHero_Name());
	var.setLevel_(getHero_Level());
	var.setDiamond(getHero_Diamond());
	var.setExp(getHero_Exp());
	var.setCurLevelMaxExp(getHero_CurLevelMaxExp());
	var.setStrength(getHero_Strength());
	var.setMoney(getHero_Money());
	var.setTeamLv(getHero_TeamLv());
	var.setRank(getHero_Rank());
	CardTeam::sharedCardTeam()->getCardTeamPor();//读取卡牌团队的档
}
//设置游戏存档
void Archives::setHero_property(const Hero &var)
{
	CCUserDefault* userdefault = CCUserDefault::sharedUserDefault();
	userdefault->setStringForKey("Hero_Name",var.getName_());
	userdefault->setIntegerForKey("Hero_Level",var.getLevel_());
	userdefault->setIntegerForKey("Hero_Diamond",var.getDiamond());
	userdefault->setIntegerForKey("Hero_Exp",var.getExp());
	userdefault->setIntegerForKey("Hero_CurLevelMaxExp",var.getCurLevelMaxExp());
	userdefault->setIntegerForKey("Hero_Strength",var.getStrength());
	userdefault->setIntegerForKey("Hero_Money",var.getMoney());
	userdefault->setIntegerForKey("Hero_TeamLv",var.getTeamLv());
	userdefault->setIntegerForKey("Hero_Rank",var.getRank());
	userdefault->flush();
	CardTeam::sharedCardTeam()->setCardTeamPor();//存卡牌团队的档
}

void Archives::setHero_Name(string var)
{
	CCUserDefault::sharedUserDefault()->setStringForKey("Hero_Name",var);
	CCUserDefault::sharedUserDefault()->flush();
}

string Archives::getHero_Name()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey("Hero_Name","null");
}

void Archives::setHero_Level(int var)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Hero_Level",var);
	CCUserDefault::sharedUserDefault()->flush();
}

int Archives::getHero_Level()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("Hero_Level",0);
}

void Archives::setHero_Diamond(int var)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Hero_Diamond",var);
	CCUserDefault::sharedUserDefault()->flush();
}

int Archives::getHero_Diamond()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("Hero_Diamond",0);
}

void Archives::setHero_Exp(int var)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Hero_Exp",var);
	CCUserDefault::sharedUserDefault()->flush();
}

int Archives::getHero_Exp()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("Hero_Exp",0);
}

void Archives::setHero_CurLevelMaxExp(int var)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Hero_CurLevelMaxExp",var);
	CCUserDefault::sharedUserDefault()->flush();
}

int Archives::getHero_CurLevelMaxExp()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("Hero_CurLevelMaxExp",0);
}

void Archives::setHero_Strength(int var)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Hero_Strength",var);
	CCUserDefault::sharedUserDefault()->flush();
}

int Archives::getHero_Strength()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("Hero_Strength",0);
}

void Archives::setHero_Money(int var)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Hero_Money",var);
	CCUserDefault::sharedUserDefault()->flush();
}

int Archives::getHero_Money()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("Hero_Money",0);
}

void Archives::setHero_TeamLv(int var)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Hero_TeamLv",var);
	CCUserDefault::sharedUserDefault()->flush();
}

int Archives::getHero_TeamLv()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("Hero_TeamLv",1);
}

void Archives::setHero_Rank(int var)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("Hero_Rank",var);
	CCUserDefault::sharedUserDefault()->flush();
}

int Archives::getHero_Rank()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("Hero_Rank",1);
}


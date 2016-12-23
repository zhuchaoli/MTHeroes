#include "Hero.h"
Hero* Hero::m_pHero = NULL;

Hero::Hero()
{
	getHero_Property();
}
Hero* Hero::sharedHero()
{
	if(!m_pHero)
	{
		m_pHero = new Hero();
	}
	CCAssert(m_pHero,"创建主角失败");//加上断言
	return m_pHero;
}

void Hero::getHero_Property()
{
	CCUserDefault* userdefault = CCUserDefault::sharedUserDefault();
	m_name = userdefault->getStringForKey("Hero_Name","zhuchaoli");
	m_level = userdefault->getIntegerForKey("Hero_Level",1);
	m_diamond = userdefault->getIntegerForKey("Hero_Diamond",0);
	m_exp = userdefault->getIntegerForKey("Hero_Exp",0);
	m_curlevelmaxexp = userdefault->getIntegerForKey("Hero_CurLevelMaxExp",100);
	m_strength = userdefault->getIntegerForKey("Hero_Strength",0);
	m_money = userdefault->getIntegerForKey("Hero_Money",0);
	m_teamlv = userdefault->getIntegerForKey("Hero_TeamLv",2141);
	m_rank = userdefault->getIntegerForKey("Hero_Rank",1);
}

void Hero::setHero_property()
{
	CCUserDefault* userdefault = CCUserDefault::sharedUserDefault();
	userdefault->setStringForKey("Hero_Name",getName_());
	userdefault->setIntegerForKey("Hero_Level",getLevel_());
	userdefault->setIntegerForKey("Hero_Diamond",getDiamond());
	userdefault->setIntegerForKey("Hero_Exp",getExp());
	userdefault->setIntegerForKey("Hero_CurLevelMaxExp",getCurLevelMaxExp());
	userdefault->setIntegerForKey("Hero_Strength",getStrength());
	userdefault->setIntegerForKey("Hero_Money",getMoney());
	userdefault->setIntegerForKey("Hero_TeamLv",getTeamLv());
	userdefault->setIntegerForKey("Hero_Rank",getRank());
	userdefault->flush();
}


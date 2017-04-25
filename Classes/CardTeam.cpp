#include "CardTeam.h"

CardTeam* CardTeam::m_pCardTeam = NULL;

CardTeam::CardTeam()
{
	getCardTeamPor();//¶Áµµ
}

CardTeam* CardTeam::sharedCardTeam()
{
	if(!m_pCardTeam)
	{
		m_pCardTeam = new CardTeam();
	}
	CCAssert(m_pCardTeam,"´´½¨¿¨ÅÆÍÅ¶ÓÊ§°Ü");
	return m_pCardTeam;
}

void CardTeam::setCardTeamPor()
{
	CCUserDefault* userdef = CCUserDefault::sharedUserDefault();
	userdef->setIntegerForKey("caption_life",getcaption_life());
	userdef->setIntegerForKey("caption_attack",getcaption_attack());
	userdef->setIntegerForKey("teammate1_life",getteammate1_life());
	userdef->setIntegerForKey("teammate1_attack",getteammate1_attack());
	userdef->setIntegerForKey("teammate2_life",getteammate2_life());
	userdef->setIntegerForKey("teammate2_attack",getteammate2_attack());
	userdef->setIntegerForKey("teammate3_life",getteammate3_life());
	userdef->setIntegerForKey("teammate3_attack",getteammate3_attack());
	userdef->setIntegerForKey("teammate4_life",getteammate4_life());
	userdef->setIntegerForKey("teammate4_attack",getteammate4_attack());

	userdef->setIntegerForKey("eatedcard0count",geteatedcard0count());
	userdef->setIntegerForKey("eatedcard1count",geteatedcard1count());
	userdef->setIntegerForKey("eatedcard2count",geteatedcard2count());
	userdef->setIntegerForKey("eatedcard3count",geteatedcard3count());
	userdef->setIntegerForKey("eatedcard4count",geteatedcard4count());
	userdef->setIntegerForKey("eatedcard5count",geteatedcard5count());
	userdef->flush();
}

void CardTeam::getCardTeamPor()
{
	CCUserDefault* userdef = CCUserDefault::sharedUserDefault();
	setcaption_life(userdef->getIntegerForKey("caption_life",500));
	setcaption_attack(userdef->getIntegerForKey("caption_attack",550));
	setteammate1_life(userdef->getIntegerForKey("teammate1_life",450));
	setteammate1_attack(userdef->getIntegerForKey("teammate1_attack",350));
	setteammate2_life(userdef->getIntegerForKey("teammate2_life",480));
	setteammate2_attack(userdef->getIntegerForKey("teammate2_attack",380));
	setteammate3_life(userdef->getIntegerForKey("teammate3_life",457));
	setteammate3_attack(userdef->getIntegerForKey("teammate3_attack",456));
	setteammate4_life(userdef->getIntegerForKey("teammate4_life",300));
	setteammate4_attack(userdef->getIntegerForKey("teammate4_attack",359));

	seteatedcard0count(userdef->getIntegerForKey("eatedcard0count",2));
	seteatedcard1count(userdef->getIntegerForKey("eatedcard1count",1));
	seteatedcard2count(userdef->getIntegerForKey("eatedcard2count",2));
	seteatedcard3count(userdef->getIntegerForKey("eatedcard3count",3));
	seteatedcard4count(userdef->getIntegerForKey("eatedcard4count",2));
	seteatedcard5count(userdef->getIntegerForKey("eatedcard5count",1));
}

int CardTeam::getLifeByKey(int index)
{
	switch(index)
	{
	case 0:
		return getcaption_life();
	case 1:
		return getteammate1_life();
	case 2:
		return getteammate2_life();
	case 3:
		return getteammate3_life();
	case 4:
		return getteammate4_life();
	default:
		return -1;
	}
}

int CardTeam::getAttackByKey(int index)
{
	switch(index)
	{
	case 0:
		return getcaption_attack();
	case 1:
		return getteammate1_attack();
	case 2:
		return getteammate2_attack();
	case 3:
		return getteammate3_attack();
	case 4:
		return getteammate4_attack();
	default:
		return -1;
	}
}

void CardTeam::setLifeByKey(int index,int var)
{
	switch(index)
	{
	case 0:
		setcaption_life(getcaption_life()+var);
		break;
	case 1:
		setteammate1_life(getteammate1_life()+var);
		break;
	case 2:
		setteammate2_life(getteammate2_life()+var);
		break;
	case 3:
		setteammate3_life(getteammate3_life()+var);
		break;
	case 4:
		setteammate4_life(getteammate4_life()+var);
		break;
	default:
		break;
	}
}

void CardTeam::setAttackByKey(int index,int var)
{
	switch(index)
	{
	case 0:
		setcaption_attack(getcaption_attack()+var);
		break;
	case 1:
		setteammate1_attack(getteammate1_attack()+var);
		break;
	case 2:
		setteammate2_attack(getteammate2_attack()+var);
		break;
	case 3:
		setteammate3_attack(getteammate3_attack()+var);
		break;
	case 4:
		setteammate4_attack(getteammate4_attack()+var);
		break;
	default:
		break;
	}
}

int CardTeam::getEatedCardCountByKey(int index)
{
	switch(index)
	{
	case 0:
		return geteatedcard0count();
	case 1:
		return geteatedcard1count();
	case 2:
		return geteatedcard2count();
	case 3:
		return geteatedcard3count();
	case 4:
		return geteatedcard4count();
	case 5:
		return geteatedcard5count();
	default:
		return -1;
	}
}

void CardTeam::setEatedCardCountByKey(int index,int var)
{
	switch(index)
	{
	case 0:
		seteatedcard0count(geteatedcard0count()+var);
		break;
	case 1:
		seteatedcard1count(geteatedcard1count()+var);
		break;
	case 2:
		seteatedcard2count(geteatedcard2count()+var);
		break;
	case 3:
		seteatedcard3count(geteatedcard3count()+var);
		break;
	case 4:
		seteatedcard4count(geteatedcard4count()+var);
		break;
	case 5:
		seteatedcard5count(geteatedcard5count()+var);
		break;
	}
}

int CardTeam::getEatedCardTotalCount()
{
	int sum = m_eatedcard0count + m_eatedcard1count + m_eatedcard2count
		      + m_eatedcard3count + m_eatedcard4count + m_eatedcard5count;
	return sum;
}


#pragma once
#include "cocos2d.h"
#include "iostream"
using namespace std;
USING_NS_CC;

class CardTeam
{
private:
	CardTeam();
	static CardTeam* m_pCardTeam;
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if(CardTeam::m_pCardTeam != NULL)delete CardTeam::m_pCardTeam;
		}
	};
	static CGarbo m_garbo;//
public:
	static CardTeam* sharedCardTeam();

	CC_SYNTHESIZE(int,m_caption_life,caption_life);
	CC_SYNTHESIZE(int,m_caption_attack,caption_attack);
	CC_SYNTHESIZE(int,m_teammate1_life,teammate1_life);
	CC_SYNTHESIZE(int,m_teammate1_attack,teammate1_attack);
	CC_SYNTHESIZE(int,m_teammate2_life,teammate2_life);
	CC_SYNTHESIZE(int,m_teammate2_attack,teammate2_attack);
	CC_SYNTHESIZE(int,m_teammate3_life,teammate3_life);
	CC_SYNTHESIZE(int,m_teammate3_attack,teammate3_attack);
	CC_SYNTHESIZE(int,m_teammate4_life,teammate4_life);
	CC_SYNTHESIZE(int,m_teammate4_attack,teammate4_attack);
public:
	//存档
	void  setCardTeamPor();
	//读档
	void  getCardTeamPor();
	//由index获取队员的生命
	int getLifeByKey(int index);
	//由index获取队员的攻击
	int getAttackByKey(int index);
	//由index设置队员的生命
	void setLifeByKey(int index,int var);
	//由index设置队员的攻击
	void setAttackByKey(int index,int var);
	//由index得到卡牌的数量
	int getEatedCardCountByKey(int index);
	//由index设置卡牌的数量
	void setEatedCardCountByKey(int index,int var);
	int getEatedCardTotalCount();
//以下是吞噬卡牌的数量
	CC_SYNTHESIZE(int,m_eatedcard0count,eatedcard0count);
	CC_SYNTHESIZE(int,m_eatedcard1count,eatedcard1count);
	CC_SYNTHESIZE(int,m_eatedcard2count,eatedcard2count);
	CC_SYNTHESIZE(int,m_eatedcard3count,eatedcard3count);
	CC_SYNTHESIZE(int,m_eatedcard4count,eatedcard4count);
	CC_SYNTHESIZE(int,m_eatedcard5count,eatedcard5count);
};
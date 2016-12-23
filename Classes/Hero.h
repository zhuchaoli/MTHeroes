//主角类 是一个单例
#pragma once
#include "cocos2d.h"
#include "Archives.h"
USING_NS_CC;
using namespace std;

class Hero
{
private:
	Hero();
	static Hero* m_pHero;
	class CGarbo //垃圾工人
	{
	public:
		~CGarbo()
		{
			if(Hero::m_pHero != NULL)delete Hero::m_pHero;
		}
	};
	static CGarbo m_garbo;////定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数
	CC_SYNTHESIZE(string,m_name,Name_);//玩家名字
	CC_SYNTHESIZE(int,m_level,Level_);//等级
	CC_SYNTHESIZE(int,m_diamond,Diamond);//符石
	CC_SYNTHESIZE(int,m_exp,Exp);//经验值
	CC_SYNTHESIZE(int,m_curlevelmaxexp,CurLevelMaxExp);//当前等级的最大经验值
	CC_SYNTHESIZE(int,m_strength,Strength);//体力
	CC_SYNTHESIZE(int,m_money,Money);//金币
	CC_SYNTHESIZE(int,m_teamlv,TeamLv);//卡牌团队的实力
	CC_SYNTHESIZE(int,m_rank,Rank);//爵位 军衔
	CC_SYNTHESIZE(int,m_curchallengegq,CurChallengeGQ);//当前挑战的关卡;
public:
	static Hero* sharedHero();
	//读档
	void getHero_Property();
	//存档
	void setHero_property();
};
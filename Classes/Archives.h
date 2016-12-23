//游戏存档 也是一个单例
#pragma  once
#include "cocos2d.h"
#include "Hero.h"
#include "CardTeam.h"
USING_NS_CC;

class Archives
{
public:
	static Archives* sharedArchives();
	bool isExist();
	//
	void getHero_Property(Hero &var);
	void setHero_property(const Hero &var);
	void setHero_Name(string var);
	string getHero_Name();
	void setHero_Level(int var);
	int getHero_Level();
	void setHero_Diamond(int var);
	int getHero_Diamond();
	void setHero_Exp(int var);
	int getHero_Exp();
	void setHero_CurLevelMaxExp(int var);
	int getHero_CurLevelMaxExp();
	void setHero_Strength(int var);
	int getHero_Strength();
	void setHero_Money(int var);
	int getHero_Money();
	void setHero_TeamLv(int var);
	int getHero_TeamLv();
	void setHero_Rank(int var);
	int getHero_Rank();
private:
	Archives();
	static Archives* m_pArchives;
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if(Archives::m_pArchives != NULL)delete Archives::m_pArchives;
		}
	};
	static CGarbo m_garbo;
};

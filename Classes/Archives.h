//游戏存档 也是一个单例
#pragma  once
#include "cocos2d.h"
#include "Hero.h"
#include "CardTeam.h"
#include "GuanQiaState.h"
USING_NS_CC;

class Archives
{
private:
	Archives();
	static Archives* m_pArchives;
	class CGarbo //垃圾工人
	{
	public:
		~CGarbo()
		{
			if(Archives::m_pArchives != NULL)delete Archives::m_pArchives;
		}
	};
	static CGarbo m_garbo;
public:
	static Archives* sharedArchives();
	//读档
	void getArchives();
	//存档
	void setArchives();
};

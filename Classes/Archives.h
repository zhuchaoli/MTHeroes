//��Ϸ�浵 Ҳ��һ������
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
	class CGarbo //��������
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
	//����
	void getArchives();
	//�浵
	void setArchives();
};

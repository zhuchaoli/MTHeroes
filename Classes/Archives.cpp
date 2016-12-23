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
	CCAssert(m_pArchives,"������Ϸ�浵��ʧ��");
	return m_pArchives;
}

//��ȡ��Ϸ�浵
void Archives::getArchives()
{
	Hero::sharedHero();//��ȡ��ҵ�
	CardTeam::sharedCardTeam();//��ȡ�����Ŷӵĵ�
	GuanQiaState::sharedGuanQiaState();//��ȡ�ؿ�
}
//������Ϸ�浵
void Archives::setArchives()
{
	Hero::sharedHero()->setHero_property();//��ȡ��ҵ�
	CardTeam::sharedCardTeam()->setCardTeamPor();//�濨���Ŷӵĵ�
	GuanQiaState::sharedGuanQiaState()->setGuanQiaState();//��ؿ�
}



#include "Hero.h"
Hero* Hero::m_pHero = NULL;

Hero::Hero()
{

}
Hero* Hero::sharedHero()
{
	if(!m_pHero)
	{
		m_pHero = new Hero();
	}
	CCAssert(m_pHero,"��������ʧ��");//���϶���
	return m_pHero;
}




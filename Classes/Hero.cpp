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
	CCAssert(m_pHero,"创建主角失败");//加上断言
	return m_pHero;
}




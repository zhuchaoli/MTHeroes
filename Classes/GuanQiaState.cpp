#include "GuanQiaState.h"

GuanQiaState::GuanQiaState()
{
	getGuanQiaState();
}

GuanQiaState* GuanQiaState::m_pGuanQiaState = NULL;

GuanQiaState* GuanQiaState::sharedGuanQiaState()
{
	if(!m_pGuanQiaState)
	{
		m_pGuanQiaState = new GuanQiaState();
	}
	CCAssert(m_pGuanQiaState,"�����ؿ�ʵ��ʧ��");
	return m_pGuanQiaState;
}
//�浵
void GuanQiaState::setGuanQiaState()
{
	CCUserDefault* userdefault = CCUserDefault::sharedUserDefault();
	CCString* str = CCString::create("");
	for(int i = 0; i < 21; ++i)
	{
		str->initWithFormat("guanqia_state%d",i);
		userdefault->setBoolForKey(str->m_sString.c_str(),isComplete_GuanQia[i]);
	}
	userdefault->flush();
}
//����
void GuanQiaState::getGuanQiaState()
{
	CCUserDefault* userdefault = CCUserDefault::sharedUserDefault();
	CCString* str = CCString::create("");
	for(int i = 0; i < 21; ++i)
	{
		str->initWithFormat("guanqia_state%d",i);
		isComplete_GuanQia[i] = userdefault->getBoolForKey(str->m_sString.c_str(),false);
	}
	//����ʱ ʹ��
	isComplete_GuanQia[0] = true;
	isComplete_GuanQia[1] = true;
	isComplete_GuanQia[2] = true;
	isComplete_GuanQia[3] = true;
}


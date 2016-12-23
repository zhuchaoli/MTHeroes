//¹Ø¿¨Àà µ¥Àý
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GuanQiaState
{
private:
	GuanQiaState();
	static GuanQiaState* m_pGuanQiaState;
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if(GuanQiaState::m_pGuanQiaState != NULL)delete GuanQiaState::m_pGuanQiaState;
		}
	};
	static CGarbo m_garbo;//
	
public:
	static GuanQiaState* sharedGuanQiaState();
	bool isComplete_GuanQia[21];
	void setGuanQiaState();
	void getGuanQiaState();
};

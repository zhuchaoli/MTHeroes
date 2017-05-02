//关卡类 单例
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
	bool isComplete_GuanQia[21];//记录关卡是否通关
	void setGuanQiaState();
	void getGuanQiaState();
};

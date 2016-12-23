#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CopyrightLayer : public CCLayer
{
public:
	CREATE_FUNC(CopyrightLayer);
	bool init();
private:
	void gotoNextScene(float);//跳到下一个场景
};


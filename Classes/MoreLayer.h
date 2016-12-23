#pragma once
#include "cocos2d.h"
USING_NS_CC;

class MoreLayer:public CCLayer
{
public:
	CREATE_FUNC(MoreLayer);
	bool init();
	void initframe();
	void initMoreList();
};
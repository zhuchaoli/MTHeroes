#pragma once
#include "cocos2d.h"
USING_NS_CC;

class TastLayer:public CCLayer
{
public:
	CREATE_FUNC(TastLayer);
	bool init();
	void initframe();
	void initTastList();
	void menu_returncallback(CCObject*);
};
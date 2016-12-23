#pragma once
#include "cocos2d.h"
USING_NS_CC;

class EatedCardLayer:public CCLayer
{
public:
	CREATE_FUNC(EatedCardLayer);
	bool init();
	void initframe();
	void initCardList();
	void menu_returncallback(CCObject*);

	CCLabelTTF* eatedcardsum_value;
};
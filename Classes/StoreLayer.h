#pragma once
#include "cocos2d.h"
USING_NS_CC;

class StoreLayer:public CCLayer
{
public:
	CREATE_FUNC(StoreLayer);
	bool init();
private:
	void initframe();
	void initTitle();
	void initMenu();
	void menu_raffle_friend_callback(CCObject*);//友情抽奖
	void menu_raffle_diamon_callback(CCObject*);//符石抽奖
	void menu_buystrengthbymoney_callback(CCObject*);//花费金币购买体力
	void menu_buystrengthbydiamon_callback(CCObject*);//花费符石购买体力

	CCNode* menu;
};
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
	void menu_raffle_friend_callback(CCObject*);//����齱
	void menu_raffle_diamon_callback(CCObject*);//��ʯ�齱
	void menu_buystrengthbymoney_callback(CCObject*);//���ѽ�ҹ�������
	void menu_buystrengthbydiamon_callback(CCObject*);//���ѷ�ʯ��������

	CCNode* menu;
};
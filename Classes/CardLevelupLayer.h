#pragma once
#include "cocos2d.h"
#include "DialogStringLayer.h"
USING_NS_CC;

class CardLevelupLayer:public CCLayer
{
public:
	CREATE_FUNC(CardLevelupLayer);
	bool init();
private:
	void initframe();
	void initcontent();
	void menu_return_callback(CCObject*);//返回回调函数
	void menu_cardlevelupUI_startlevelup(CCObject*);//升级回调函数
	void menu_choose_food(CCObject*);//选择吞噬英雄回调函数
	void littlecard_flash_done(CCNode*);
	void update(float);
private:
	int addlifesum;
	int addattacksum;
	int submoneysum;
	int subdiamonsum;
	int isCardSelect[6];
	CCMenuItemSprite* choose_food_item;
	CCMenuItemSprite* startlevelup_item;

	CCNode* card;
	CCSprite* add[6];
	CCLabelTTF* lifevalue;
	CCLabelTTF* attackvalue;
	CCLabelTTF* eatmoneyvalue;
	CCLabelTTF* eatdiamonvalue;

	CCNode* littlecard[6];
	CCProgressTimer* addlife_progress;
	CCProgressTimer* addattack_progress;
};
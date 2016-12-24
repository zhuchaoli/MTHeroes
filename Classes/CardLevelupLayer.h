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
	void menu_return_callback(CCObject*);//���ػص�����
	void menu_cardlevelupUI_startlevelup(CCObject*);//�����ص�����
	void menu_choose_food(CCObject*);//ѡ������Ӣ�ۻص�����
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
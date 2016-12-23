#pragma once
#include "cocos2d.h"
#include "NorInstanceListLayer.h"
USING_NS_CC;

#define INSTANCE_UI 0
#define LINEUP_UI   1

class InstanceLayer:public CCLayer
{
public:
	CREATE_FUNC(InstanceLayer);
	bool init();
	void call_by_main();
	void restoreToInstanceUI();//返回到副本
private:
	void initframe();
	void initList();
	void return_instance(CCObject*);//
	void return_lineup(CCObject*);//
	void menu_start_battle(CCObject*);//开始战斗
private:
	int m_curUI;//当前所处的界面(副本,队形)
	NorInstanceListLayer* norinstancelayer;
	CCSprite* title_custom_instance;//副本界面标题
	CCSprite* title_custom_lineup;//队列界面的标题
	CCNode* lineup_content;//队列界面的内容

	CCMenu* menu_left_return;//返回按钮
	CCSprite* listbase;//背景
	int pos_x[5];
	int pos_y[5];
};
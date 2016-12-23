#pragma once
#include "cocos2d.h"
#include "MainUILayer.h"
#include <string>
USING_NS_CC;
using namespace std;

#define MAIN_TOP                    1
#define MAIN_TOP_STRENGTH_TIME      2
#define MAIN_TOP_STRENGTH_VALUE	    3
#define MAIN_TOP_STRENGTH_PROGERESS 4
#define MAIN_TOP_EXP                5

class MainUIScene : public CCScene
{
public:
	CREATE_FUNC(MainUIScene);
	bool init();
	void button_Homepage(CCObject*);//主页
	void button_Instance(CCObject*);//副本
	void button_Fight(CCObject*);//战斗
	void button_Store(CCObject*);//商店
	void button_More(CCObject*);//攻略
private:
	CCLayerMultiplex* multilayer;
	MainUILayer* mainuilayer;
	CCLabelTTF* text;
	CCSprite* rank;//爵位
	CCLabelTTF* lv;//等级
	CCLabelTTF* diamond;//金币
	CCLabelTTF* money;//符石
	void initSysInfoLayer();
	void configureMultiplexLayer();
	void configureTopUI();
	void configureButtonUI();
	void scrollText();//滚动文字

	void show_BattleResult(CCObject*);//显示战斗结果
	void updateMoneyAndDiamon(CCObject*);//更新金币和符石
	void updateStrengthAndExp(CCObject*);//更新体力和经验
	void update(float);
	void updateStrengthTime(float);

	string getStrengthTime(string curtime);
	int getUpLevel(int exp,int curmaxexp);//计算能升几个等级
};
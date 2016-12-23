#pragma once
#include "cocos2d.h"
#include "iostream"
using namespace std;
USING_NS_CC;

class MainTopUITouchLayer:public CCLayer
{
public:
	CREATE_FUNC(MainTopUITouchLayer);
	bool init();
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void InitSysInfo();
	string getTime();
	void updateTime(float);
private:
	CCNode* sysInfo;
};
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class BattleResultLayer : public CCLayer
{
public:
	CREATE_FUNC(BattleResultLayer);
	bool init();
	void initBK();
	void showbooty_card();

	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
private:
	int guanqia;//第几关
	int booty_card[6];//卡牌战利品
	int posx[5];
	int posy[5];
};
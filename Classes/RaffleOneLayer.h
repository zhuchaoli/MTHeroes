#pragma once
#include "cocos2d.h"
USING_NS_CC;

class RaffleOneLayer : public CCLayer
{
public:
	static CCScene* scene(int index);
	bool init();
	CREATE_FUNC(RaffleOneLayer);

	void initBK();
	void menu_comfirm_callback(CCObject*);
private:
	CCSprite* raffle_daguang_flash;//地上的光
	CCSprite* raffle_guang;//垂直光源
	CCNode* chuizhiguang;//垂直的光
	CCSprite* raffle_he_flash;//底部的八卦
	CCSprite* baixiangzhi;//白箱子
	CCSprite* xiangzhi_bottom;//箱子底部
	CCSprite* xiangzhi_top;//箱子顶部
	CCSprite* raffle_guangbai;//光白
	CCLayerColor* white_layer;
private:
	void show_chuizhiguang();
	void chuizhiguang_done();
	void show_xiangzhi();
	void remove_xiangzhiandguang();
	void remove_whitelayer();
	void show_card();
	void show_menu();
public:
	static int rand_cardindex;
};
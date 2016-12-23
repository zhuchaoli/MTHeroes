#pragma once
#include "cocos2d.h"
USING_NS_CC;

class RaffleTenLayer : public CCLayer
{
public:
	static CCScene* scene(int* cards);
	bool init();
	CREATE_FUNC(RaffleTenLayer);

	void initBK();
	void menu_comfirm_callback(CCObject*);
private:
	CCNode* animationNode;
	CCSprite* raffle_daguang_flash;//地上的光
	CCSprite* raffle_guang;//垂直光源
	CCNode* chuizhiguang;//垂直的光
	CCSprite* raffle_he_flash;//底部的八卦
	CCSprite* baixiangzhi;//白箱子
	CCSprite* xiangzhi_bottom;//箱子底部
	CCSprite* xiangzhi_top;//箱子顶部
	CCSprite* xiangzhi_top_new;//新箱子顶部
	CCSprite* raffle_guangbai;//光白
	
	int m_cardth;
	int m_posx[10];
	int m_posy[10];
private:
	void show_chuizhiguang();
	void chuizhiguang_done();
	void show_xiangzhi();
	void remove_xiangzhiandguang();
	void show_card();
	void show_menu();
	void show_box_card(float);
	void show_box_card_front(float);
	void remove_box_card(CCNode*);
	static int* pcards;
};
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
	CCSprite* raffle_daguang_flash;//���ϵĹ�
	CCSprite* raffle_guang;//��ֱ��Դ
	CCNode* chuizhiguang;//��ֱ�Ĺ�
	CCSprite* raffle_he_flash;//�ײ��İ���
	CCSprite* baixiangzhi;//������
	CCSprite* xiangzhi_bottom;//���ӵײ�
	CCSprite* xiangzhi_top;//���Ӷ���
	CCSprite* raffle_guangbai;//���
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
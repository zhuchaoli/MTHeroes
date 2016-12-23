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
	CCSprite* raffle_daguang_flash;//���ϵĹ�
	CCSprite* raffle_guang;//��ֱ��Դ
	CCNode* chuizhiguang;//��ֱ�Ĺ�
	CCSprite* raffle_he_flash;//�ײ��İ���
	CCSprite* baixiangzhi;//������
	CCSprite* xiangzhi_bottom;//���ӵײ�
	CCSprite* xiangzhi_top;//���Ӷ���
	CCSprite* xiangzhi_top_new;//�����Ӷ���
	CCSprite* raffle_guangbai;//���
	
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
#pragma once
#include "cocos2d.h"
#include "ArenaListLayer.h"
USING_NS_CC;

#define ARENA_UI   0
#define LINEUP_UI  1

class ArenaLayer:public CCLayer
{
public:
	CREATE_FUNC(ArenaLayer);
	bool init();
	void call_by_main();
	void restoreToArenaUI();//���ص�ս��
private:
	void initframe();
	void initList();
	void return_arena(CCObject*);//
	void return_lineup(CCObject*);//
	void menu_start_battle(CCObject*);//��ʼս��
private:
	int m_curUI;//��ǰ�����Ľ���(ս��,����)
	ArenaListLayer* arenalistlayer;
	CCSprite* title_custom_arena;//ս���������
	CCSprite* title_custom_lineup;//���н���ı���
	CCNode* lineup_content;//���н��������

	CCMenu* menu_left_return;//���ذ�ť
	CCSprite* listbase;//����
	int pos_x[5];
	int pos_y[5];
};
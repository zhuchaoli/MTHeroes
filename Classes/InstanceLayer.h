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
	void restoreToInstanceUI();//���ص�����
private:
	void initframe();
	void initList();
	void return_instance(CCObject*);//
	void return_lineup(CCObject*);//
	void menu_start_battle(CCObject*);//��ʼս��
private:
	int m_curUI;//��ǰ�����Ľ���(����,����)
	NorInstanceListLayer* norinstancelayer;
	CCSprite* title_custom_instance;//�����������
	CCSprite* title_custom_lineup;//���н���ı���
	CCNode* lineup_content;//���н��������

	CCMenu* menu_left_return;//���ذ�ť
	CCSprite* listbase;//����
	int pos_x[5];
	int pos_y[5];
};
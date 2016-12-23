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
	void button_Homepage(CCObject*);//��ҳ
	void button_Instance(CCObject*);//����
	void button_Fight(CCObject*);//ս��
	void button_Store(CCObject*);//�̵�
	void button_More(CCObject*);//����
private:
	CCLayerMultiplex* multilayer;
	MainUILayer* mainuilayer;
	CCLabelTTF* text;
	CCSprite* rank;//��λ
	CCLabelTTF* lv;//�ȼ�
	CCLabelTTF* diamond;//���
	CCLabelTTF* money;//��ʯ
	void initSysInfoLayer();
	void configureMultiplexLayer();
	void configureTopUI();
	void configureButtonUI();
	void scrollText();//��������

	void show_BattleResult(CCObject*);//��ʾս�����
	void updateMoneyAndDiamon(CCObject*);//���½�Һͷ�ʯ
	void updateStrengthAndExp(CCObject*);//���������;���
	void update(float);
	void updateStrengthTime(float);

	string getStrengthTime(string curtime);
	int getUpLevel(int exp,int curmaxexp);//�������������ȼ�
};
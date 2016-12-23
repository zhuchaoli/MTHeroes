#pragma once
#include "cocos2d.h"
#include "MailLayer.h"
#include "CardLevelupLayer.h"
#include "EatedCardLayer.h"
#include "TastLayer.h"
USING_NS_CC;

//���嵱ǰ�����ĸ�����
enum MainUI_CurUI
{
	MAIN_UI,    /*������*/
	MAIL_UI,    /*����*/
	CARD_UI,   /*Ӣ��(���ƽ�ɫ)*/
	LEVELUP_UI,/*����*/
	TAST_UI,/*����*/
	SALE_UI/**/
};

class MainUILayer : public CCLayer
{
public:
	CREATE_FUNC(MainUILayer);
	bool init();
	void restoreToMainUI();
private:
	void returncallback(CCObject*);
	void configureTeamUI();
	void configureMenuUI();
	void menu_selectcardcallback(CCObject*);
	void menu_mailcallback(CCObject*);
	void showMailUI();
	void menu_cardcallback(CCObject*);
	void showCardUI();
	void menu_cardlevelupcallback(CCObject*);
	void showCardLevelupUI();
	void menu_tastcallback(CCObject*);
	void showTastUI();
	void menu_salecallback(CCObject*);
	void showSaleUI();
	void textlevel_flash(float);
private:
	MainUI_CurUI m_curUI;
	CCSprite* team;
	CCNode* menu;
	CCSprite* text_max[5];
	CCNode* text_level[5];//��Աʵ��
	CCSprite* role_frame[5];

	MailLayer* mailUI;
	CardLevelupLayer* levelupUI;
	EatedCardLayer* cardUI;
	TastLayer* tastUI;
};
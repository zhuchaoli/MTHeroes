#pragma once
#include "cocos2d.h"
#include "MailLayer.h"
#include "CardLevelupLayer.h"
#include "EatedCardLayer.h"
#include "TastLayer.h"
USING_NS_CC;

//定义当前处在哪个界面
enum MainUI_CurUI
{
	MAIN_UI,    /*主界面*/
	MAIL_UI,    /*邮箱*/
	CARD_UI,   /*英雄(卡牌角色)*/
	LEVELUP_UI,/*升级*/
	TAST_UI,/*奖励*/
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
	CCNode* text_level[5];//队员实力
	CCSprite* role_frame[5];

	MailLayer* mailUI;
	CardLevelupLayer* levelupUI;
	EatedCardLayer* cardUI;
	TastLayer* tastUI;
};
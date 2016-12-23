#pragma once
#include "cocos2d.h"
USING_NS_CC;

class MailLayer : public CCLayer
{
public:
	CREATE_FUNC(MailLayer);
	bool init();
private:
	void initframe();
	void menu_returncallback(CCObject*);
	void addmail();//Ìí¼ÓÓÊ¼þ
	void moneymenu_callback(CCObject*);
	void diamonmenu_callback(CCObject*);
private:
	CCMenu* moneymenu;
	CCMenu* diamonmenu;
	CCSprite* img_h1;
	CCSprite* img_h2;
	CCSprite* money_sign1;
	CCSprite* money_sign2;
	CCSprite* diamon_sign1;
	CCSprite* diamon_sign2;
};
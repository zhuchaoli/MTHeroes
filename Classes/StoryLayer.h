#pragma once
#include "cocos2d.h"
USING_NS_CC;

class StoryLayer : public CCLayer
{
public:
	CREATE_FUNC(StoryLayer);
	bool init();
	void update(float);
private:
	void passStory(CCObject *);//跳过开场动画
	void beginScene1();
	void endScene1(float);
	void beginScene2();
	void endScene2(float);
	void beginScene3();
	void endScene3(float);
	void beginScene4();
	void endScene4(float);
	void beginScene5();
	void endScene5(float);
	void xingxingFlash();
	void showText1(float);
	void showText2(float);
	void showText3(float);
	void showText4(float);
	void showText5(float);
	void showText6(float);
	void showText7(float);
	void showText8(float);
	void showText9(float);
	void showText10(float);
	void showText11(float);
	void showText12(float);
	void showText13(float);
	void showText14(float);
	void showText(CCSprite* &spr,const char * name,float dt=1.0f,CCPoint initpos = ccp(20,80),CCPoint movepos = ccp(0,80),bool isDisappear = true);
	void removeSprite(CCNode* node,void* data);
	void shakeHead(CCSprite* &spr);
	void showTextBox(CCSprite* &spr,const char * name,CCPoint inipos);
private:
	CCSprite * background1;
	CCSprite * background2;
	CCSprite * background3;
	CCSprite * xingxing;
	//第二幕
	CCSprite * huodui;
	CCSprite * play_dede;
	CCSprite * play_shaman;
	CCSprite * play_mt;
	CCSprite * text3box;
	CCSprite * text4box;
	CCSprite * text5box;
	CCSprite * text6box;
	CCSprite * text7box;
	//第三幕
	CCSprite * guangxian;
	CCSprite * shiren1;
	CCSprite * shiren2;
	CCSprite * shiren3;
	CCSprite * tianhuo1;
	CCSprite * tianhuo2;
	CCSprite * tianhuo31;
	CCSprite * tianhuo32;
	CCSprite * tianhuo33;

	CCSprite * text[14];
};
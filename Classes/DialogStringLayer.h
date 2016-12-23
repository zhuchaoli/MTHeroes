#pragma once
#include "cocos2d.h"
USING_NS_CC;

class DialogStringLayer:public CCLayerColor
{
public:
	static DialogStringLayer* create(const char* strmsg);
	bool init(const char* strmsg);
	void onEnter();
	void onExit();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	//初始化对话框
	bool onInitDialog(const char* strmsg);
	//将所有菜单按钮压入容器中
	void pushMenu(CCMenuItem * );
	void menu_confirmcallback(CCObject*);
private:
	CCMenu* menu;
	CCArray* menuitemarr;//所有的菜单项
	bool touchmenu;//记录是否点中菜单
};
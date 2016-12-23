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
	//��ʼ���Ի���
	bool onInitDialog(const char* strmsg);
	//�����в˵���ťѹ��������
	void pushMenu(CCMenuItem * );
	void menu_confirmcallback(CCObject*);
private:
	CCMenu* menu;
	CCArray* menuitemarr;//���еĲ˵���
	bool touchmenu;//��¼�Ƿ���в˵�
};
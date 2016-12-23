#pragma once
#include "cocos2d.h"
USING_NS_CC;

class LoginLayer : public CCLayer
{
public:
	CREATE_FUNC(LoginLayer);
	bool init();
private:
	void initUI();
	void initWebView();
	void startGame(CCObject *);
};
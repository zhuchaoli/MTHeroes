#pragma once
#include "cocos2d.h"
#include "LoginLayer.h"
USING_NS_CC;

class LoginScene : public CCScene
{
public:
	CREATE_FUNC(LoginScene);
	bool init();
private:
	LoginLayer * loginLayer;
};
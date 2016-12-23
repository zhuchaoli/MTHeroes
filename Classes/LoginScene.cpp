#include "LoginScene.h"

bool LoginScene::init()
{
	if(!CCScene::init())return false;
	this->loginLayer = LoginLayer::create();
	this->addChild(this->loginLayer);
	return true;
}


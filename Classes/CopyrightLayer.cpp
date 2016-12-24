#include "CopyrightLayer.h"
#include "LoginScene.h"
#include "AppMacros.h"

bool CopyrightLayer::init()
{
	if(!CCLayer::init())return false;
	CCSprite * logo = CCSprite::create("ui/logo.png");
	logo->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(logo);
	//1.5s后跳到下一个场景
	scheduleOnce(schedule_selector(CopyrightLayer::gotoNextScene),1.5f);//要改回1.5f 目前处于调试阶段
	return true;
}

void CopyrightLayer::gotoNextScene(float dt)
{
	LoginScene * loginScene = LoginScene::create();
	CCDirector::sharedDirector()->replaceScene(loginScene);
}

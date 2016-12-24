#include "CopyrightLayer.h"
#include "LoginScene.h"
#include "AppMacros.h"

bool CopyrightLayer::init()
{
	if(!CCLayer::init())return false;
	CCSprite * logo = CCSprite::create("ui/logo.png");
	logo->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(logo);
	//1.5s��������һ������
	scheduleOnce(schedule_selector(CopyrightLayer::gotoNextScene),1.5f);//Ҫ�Ļ�1.5f Ŀǰ���ڵ��Խ׶�
	return true;
}

void CopyrightLayer::gotoNextScene(float dt)
{
	LoginScene * loginScene = LoginScene::create();
	CCDirector::sharedDirector()->replaceScene(loginScene);
}

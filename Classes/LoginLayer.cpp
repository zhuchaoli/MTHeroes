#include "LoginLayer.h"
#include "StoryScene.h"
#include "AppMacros.h"

bool LoginLayer::init()
{
	if(!CCLayer::init())return false;
	//登录场景的背景音乐
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/startgame.mp3",true);//循环播放
	initUI();
	return true;
}

void LoginLayer::initUI()
{
	//加载背景
	CCSprite * background = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_bei.png"));
	background->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	background->setScale(1.877f);
	this->addChild(background);
	//加载logo
	CCSprite * logo = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_logo.png"));
	logo->setAnchorPoint(ccp(0,1));
	logo->setPosition(ccp(15,visibleSize.height-40));
	this->addChild(logo);
	//加载大小姐
	CCSprite * daxiaojie = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_daxiaojie.png"));
	daxiaojie->setAnchorPoint(ccp(1,0));
	daxiaojie->setPosition(ccp(visibleSize.width+daxiaojie->getContentSize().width,visibleSize.height/2*0.8));
	//daxiaojie->setScale(0.65f);
	this->addChild(daxiaojie);
	CCMoveBy* daxiaojieMove = CCMoveBy::create(0.2f,ccp(-daxiaojie->getContentSize().width,0));
	daxiaojie->runAction(daxiaojieMove);
	//加载傻馒
	CCSprite * shaman = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_shaman.png"));
	shaman->setAnchorPoint(ccp(0,1));
	shaman->setPosition(ccp(-shaman->getContentSize().width,visibleSize.height/2*1.2));
	//shaman->setScale(0.6f);
	this->addChild(shaman);
	CCMoveBy* shamanMove = CCMoveBy::create(0.2f,ccp(shaman->getContentSize().width,0));
	shaman->runAction(shamanMove);
	//显示版本号
	CCLabelTTF * version = CCLabelTTF::create("v1.0.0","Arial",25);
	version->setPosition(ccp(version->getContentSize().width/2,visibleSize.height-version->getContentSize().height/2));
	this->addChild(version);
	//加载底部黑框
	CCSprite * heikuang = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_heikuang.png"));
	heikuang->setPosition(ccp(visibleSize.width/2,heikuang->getContentSize().height/2));
	heikuang->setScaleX(10.67f);
	this->addChild(heikuang);
	//加载底部文字
	CCSprite * wenzhi = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_wenzhi.png"));
	wenzhi->setPosition(ccp(visibleSize.width/2,wenzhi->getContentSize().height/2 + 7));
	this->addChild(wenzhi);
	//添加离散效果
	CCSprite * suduxian = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_suduxian.png"));
	suduxian->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	suduxian->setScale(1.877f);
	this->addChild(suduxian);
	//加载开始游戏背景
	CCSprite * startGameBackground = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_textbase.png"));
	startGameBackground->setPosition(ccp(visibleSize.width/2,130));
	startGameBackground->setScale(1.877f);
	this->addChild(startGameBackground);
	//加载开始游戏菜单
	CCSprite * startGameNor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Textrue_stargame.png"));
	CCSprite * startGameSel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Textrue_stargame.png"));
	CCMenuItemSprite* startGameItem = CCMenuItemSprite::create(startGameNor,
		                                                       startGameSel,
															   this,
															   menu_selector(LoginLayer::startGame));
	CCMenu * startGameMenu = CCMenu::create(startGameItem,NULL);
	startGameItem->setPosition(ccp(visibleSize.width/2,115));
	startGameMenu->setPosition(ccp(0,0));
	this->addChild(startGameMenu);
	//开始游戏的文字变大变小
	CCScaleTo * startGameBig = CCScaleTo::create(0.4f,1.02f);
	CCScaleTo * startGameLitter = CCScaleTo::create(0.4f,1.0f);
	CCSequence * seq = CCSequence::create(startGameBig,startGameLitter,NULL);
	startGameMenu->runAction(CCRepeatForever::create(seq));
}

//跳转到开场动画场景
void LoginLayer::startGame(CCObject *pSender)
{
	StoryScene * storyScene = StoryScene::create();
	CCDirector::sharedDirector()->replaceScene(storyScene);
}


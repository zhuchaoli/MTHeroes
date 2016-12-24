#include "LoginLayer.h"
#include "StoryScene.h"
#include "AppMacros.h"

bool LoginLayer::init()
{
	if(!CCLayer::init())return false;
	//��¼�����ı�������
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/startgame.mp3",true);//ѭ������
	initUI();
	return true;
}

void LoginLayer::initUI()
{
	//���ر���
	CCSprite * background = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_bei.png"));
	background->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	background->setScale(1.877f);
	this->addChild(background);
	//����logo
	CCSprite * logo = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_logo.png"));
	logo->setAnchorPoint(ccp(0,1));
	logo->setPosition(ccp(15,visibleSize.height-40));
	this->addChild(logo);
	//���ش�С��
	CCSprite * daxiaojie = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_daxiaojie.png"));
	daxiaojie->setAnchorPoint(ccp(1,0));
	daxiaojie->setPosition(ccp(visibleSize.width+daxiaojie->getContentSize().width,visibleSize.height/2*0.8));
	//daxiaojie->setScale(0.65f);
	this->addChild(daxiaojie);
	CCMoveBy* daxiaojieMove = CCMoveBy::create(0.2f,ccp(-daxiaojie->getContentSize().width,0));
	daxiaojie->runAction(daxiaojieMove);
	//����ɵ��
	CCSprite * shaman = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_shaman.png"));
	shaman->setAnchorPoint(ccp(0,1));
	shaman->setPosition(ccp(-shaman->getContentSize().width,visibleSize.height/2*1.2));
	//shaman->setScale(0.6f);
	this->addChild(shaman);
	CCMoveBy* shamanMove = CCMoveBy::create(0.2f,ccp(shaman->getContentSize().width,0));
	shaman->runAction(shamanMove);
	//��ʾ�汾��
	CCLabelTTF * version = CCLabelTTF::create("v1.0.0","Arial",25);
	version->setPosition(ccp(version->getContentSize().width/2,visibleSize.height-version->getContentSize().height/2));
	this->addChild(version);
	//���صײ��ڿ�
	CCSprite * heikuang = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_heikuang.png"));
	heikuang->setPosition(ccp(visibleSize.width/2,heikuang->getContentSize().height/2));
	heikuang->setScaleX(10.67f);
	this->addChild(heikuang);
	//���صײ�����
	CCSprite * wenzhi = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_wenzhi.png"));
	wenzhi->setPosition(ccp(visibleSize.width/2,wenzhi->getContentSize().height/2 + 7));
	this->addChild(wenzhi);
	//�����ɢЧ��
	CCSprite * suduxian = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_suduxian.png"));
	suduxian->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	suduxian->setScale(1.877f);
	this->addChild(suduxian);
	//���ؿ�ʼ��Ϸ����
	CCSprite * startGameBackground = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_textbase.png"));
	startGameBackground->setPosition(ccp(visibleSize.width/2,130));
	startGameBackground->setScale(1.877f);
	this->addChild(startGameBackground);
	//���ؿ�ʼ��Ϸ�˵�
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
	//��ʼ��Ϸ�����ֱ���С
	CCScaleTo * startGameBig = CCScaleTo::create(0.4f,1.02f);
	CCScaleTo * startGameLitter = CCScaleTo::create(0.4f,1.0f);
	CCSequence * seq = CCSequence::create(startGameBig,startGameLitter,NULL);
	startGameMenu->runAction(CCRepeatForever::create(seq));
}

//��ת��������������
void LoginLayer::startGame(CCObject *pSender)
{
	StoryScene * storyScene = StoryScene::create();
	CCDirector::sharedDirector()->replaceScene(storyScene);
}


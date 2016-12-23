#include "MoreLayer.h"
#include "MoreListLayer.h"
#include "AppMacros.h"
#include "AppStringFile.h"

bool MoreLayer::init()
{
	if(!CCLayer::init())return false;
	initframe();
	return true;
}

void MoreLayer::initframe()
{
	//¿¨ÅÆ±³¾°
	CCSprite* listbase = CCSprite::create("ui/listbase_1.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(ccp(visibleSize.width/2,410));
	this->addChild(listbase);
	//³õÊ¼»¯¹¥ÂÔÁÐ±í
	initMoreList();
	//±³¾°
	CCSprite* background = CCSprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(ccp(visibleSize.width/2,760));
	this->addChild(background);
	//µ×²¿±³¾°
	CCSprite* bottom_list = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bottom_list.jpg"));
	bottom_list->setPosition(ccp(visibleSize.width/2,bottom_list->getContentSize().height/2));
	this->addChild(bottom_list);
	//¶¥²¿ÎÄ×Ö±³¾°
	CCSprite* middletitlebase = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("middletitlebase.png"));
	middletitlebase->setPosition(ccp(visibleSize.width/2,700));
	this->addChild(middletitlebase);
	//¶¥²¿ÎÄ×Ö
	CCSprite* titlenamemycard = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("titlename_help.png"));
	titlenamemycard->setPosition(ccp(visibleSize.width/2,690));
	this->addChild(titlenamemycard);
}

void MoreLayer::initMoreList()
{
	MoreListLayer* layer = MoreListLayer::create();
	layer->setPosition(ccp(20,160));
	this->addChild(layer);
}
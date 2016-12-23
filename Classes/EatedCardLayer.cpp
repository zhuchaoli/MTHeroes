#include "EatedCardLayer.h"
#include "EatedCardListLayer.h"
#include "AppMacros.h"
#include "AppStringFile.h"
#include "CardTeam.h"

bool EatedCardLayer::init()
{
	if(!CCLayer::init())return false;
	initframe();
	return true;
}

void EatedCardLayer::initframe()
{
	//¿¨ÅÆ±³¾°
	CCSprite* listbase = CCSprite::create("ui/listbase_1.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(ccp(visibleSize.width/2,410));
	this->addChild(listbase);
	//³õÊ¼»¯¿¨ÅÆÁÐ±í
	initCardList();
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
	CCSprite* titlenamemycard = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("titlename_mycard.png"));
	titlenamemycard->setPosition(ccp(visibleSize.width/2,690));
	this->addChild(titlenamemycard);
	//·µ»Ø°´Å¥
	CCSprite* button_left_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_0.png"));
	CCSprite* button_left_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_1.png"));
	CCSprite* button_left_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_2.png"));
	CCMenuItemSprite* button_left_item = CCMenuItemSprite::create(button_left_nor,
																	button_left_sel,
																	button_left_disable,
																	this,
																	menu_selector(EatedCardLayer::menu_returncallback));
	CCSprite* text_return = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_return.png"));
	text_return->setPosition(ccp(button_left_nor->getContentSize().width/2-15,button_left_nor->getContentSize().height/2));
	button_left_item->addChild(text_return);
	CCMenu* button_left_menu = CCMenu::create(button_left_item,NULL);
	button_left_menu->setPosition(ccp(button_left_nor->getContentSize().width/2-10,687));
	this->addChild(button_left_menu);
	//ÓÒÏÂ½Ç¿¨ÅÆÊýÁ¿
	CCSprite* num_base = CCSprite::create("ui/number_base.png");
	num_base->setScale(1.2f);
	num_base->setPosition(ccp(550,175));
	this->addChild(num_base);
	
	CCLabelTTF* eatedcardsum_text = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcardsum_text"),"Arial",18);
	eatedcardsum_text->setPosition(ccp(42,10));
	num_base->addChild(eatedcardsum_text);
	CCString* str = CCString::createWithFormat("%d",CardTeam::sharedCardTeam()->getEatedCardTotalCount());
	eatedcardsum_value = CCLabelTTF::create(str->m_sString.c_str(),"Arial",18);
	eatedcardsum_value->setPosition(ccp(90,10));
	num_base->addChild(eatedcardsum_value);
}

void EatedCardLayer::initCardList()
{
	EatedCardListLayer* layer = EatedCardListLayer::create();
	layer->setPosition(ccp(20,160));
	this->addChild(layer);
}

void EatedCardLayer::menu_returncallback(CCObject*)
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification("ReturnToMain");
}
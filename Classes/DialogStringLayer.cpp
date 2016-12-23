#include "DialogStringLayer.h"
#include "AppMacros.h"

DialogStringLayer* DialogStringLayer::create(const char* strmsg)
{
	DialogStringLayer *pRet = new DialogStringLayer(); 
	if (pRet && pRet->init(strmsg)) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}

bool DialogStringLayer::init(const char* strmsg)
{
	if(!CCLayerColor::initWithColor(ccc4(0,0,0,125)))return false;
	setTouchEnabled(true);
	menuitemarr = CCArray::create();
	menuitemarr->retain();
	touchmenu = false;
	onInitDialog(strmsg);
	menu = CCMenu::createWithArray(menuitemarr);
	menu->setPosition(ccp(0,0));
	this->addChild(menu);
	return true;
}

void DialogStringLayer::onEnter()
{
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,kCCMenuHandlerPriority-1,true);
}

void DialogStringLayer::onExit()
{
	CCLayerColor::onExit();
	menuitemarr->release();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool DialogStringLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	touchmenu = menu->ccTouchBegan(pTouch,pEvent);
	return true;
}

void DialogStringLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(touchmenu)
	{
		menu->ccTouchMoved(pTouch,pEvent);
	}
}

void DialogStringLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(touchmenu)
	{
		menu->ccTouchEnded(pTouch,pEvent);
		touchmenu = false;
	}
}

void DialogStringLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	if(touchmenu)
	{
		menu->ccTouchCancelled(pTouch,pEvent);
		touchmenu = false;
	}
}

bool DialogStringLayer::onInitDialog(const char* strmsg)
{
	//提示信息背景
	CCSprite* bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tipsbase.png"));
	bk->setScaleY(1.8f);
	bk->setPosition(ccp(winSize.width/2,winSize.height/2+150));
	this->addChild(bk);
	//文字
	CCLabelTTF* text = CCLabelTTF::create(strmsg,"Arial",35);
	text->setPosition(ccp(winSize.width/2,winSize.height/2+190));
	this->addChild(text);

	CCSprite* confirm_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_0.png"));
	CCSprite* confirm_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_2.png"));
	CCSprite* confirm_diable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_2.png"));
	CCMenuItemSprite* item = CCMenuItemSprite::create(confirm_nor,
													confirm_sel,
													confirm_diable,
													this,
													menu_selector(DialogStringLayer::menu_confirmcallback));
	CCSprite* confirm_text = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_confirm2.png"));
	confirm_text->setAnchorPoint(ccp(0.5,0.5));
	confirm_text->setPosition(ccp(100,48));
	item->addChild(confirm_text);
	item->setPosition(ccp(winSize.width/2,winSize.height/2 + 100));
	pushMenu(item);
	return true;
}

void DialogStringLayer::pushMenu(CCMenuItem * pMenuItem)
{
	menuitemarr->addObject(pMenuItem);
}

void DialogStringLayer::menu_confirmcallback(CCObject*)
{
	this->removeFromParentAndCleanup(true);
}


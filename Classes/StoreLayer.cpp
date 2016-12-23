#include "StoreLayer.h"
#include "AppStringFile.h"
#include "AppMacros.h"
#include "DialogStringLayer.h"
#include "RaffleOneLayer.h"
#include "RaffleTenLayer.h"
#include "Hero.h"
#include "CardTeam.h"

bool StoreLayer::init()
{
	if(!CCLayer::init())return false;
	srand(time(NULL));
	initframe();
	initTitle();
	initMenu();
	return true;
}

void StoreLayer::initframe()
{
	//上方背景
	CCSprite* listbase = CCSprite::create("ui/listbase_1.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(ccp(visibleSize.width/2,410));
	this->addChild(listbase);
	//背景
	CCSprite* background = CCSprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(ccp(visibleSize.width/2,760));
	this->addChild(background);
	//底部背景
	CCSprite* bottom_list = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bottom_list.jpg"));
	bottom_list->setPosition(ccp(visibleSize.width/2,bottom_list->getContentSize().height/2));
	this->addChild(bottom_list);
	//顶部文字背景
	CCSprite* middletitlebase = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("middletitlebase.png"));
	middletitlebase->setPosition(ccp(visibleSize.width/2,700));
	this->addChild(middletitlebase);
	//添加百宝箱
	//箱子底部
	CCSprite* xiangzhi_bottom = CCSprite::createWithSpriteFrameName("raffle_xiangqian2.png");
	xiangzhi_bottom->setPosition(ccp(visibleSize.width/2,visibleSize.height/2-250));
	xiangzhi_bottom->setScale(1.1f);
	this->addChild(xiangzhi_bottom);
	//箱子顶部
	CCSprite* xiangzhi_top = CCSprite::createWithSpriteFrameName("raffle_xianggai2.png");
	xiangzhi_top->setPosition(ccp(visibleSize.width/2,visibleSize.height/2-150));
	xiangzhi_top->setScale(1.1f);
	this->addChild(xiangzhi_top);
}
//添加标题
void StoreLayer::initTitle()
{
	//顶部文字
	CCSprite* titlenamemycard = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("titlename_store.png"));
	titlenamemycard->setPosition(ccp(visibleSize.width/2,690));
	this->addChild(titlenamemycard);
}

void StoreLayer::initMenu()
{
	menu = CCNode::create();
	this->addChild(menu);
	//友情抽奖
	CCSprite* button_friend_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* button_friend_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* button_friend_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	CCMenuItemSprite* button_friend_item = CCMenuItemSprite::create(button_friend_nor,
																	button_friend_sel,
																	button_friend_disable,
																	this,
																	menu_selector(StoreLayer::menu_raffle_friend_callback));
	CCSprite* text_friend = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("raffle_friend.png"));
	text_friend->setPosition(ccp(button_friend_nor->getContentSize().width/2,button_friend_nor->getContentSize().height/2));
	button_friend_item->addChild(text_friend);
	//符石抽奖
	CCSprite* button_diamon_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* button_diamon_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* button_diamon_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	CCMenuItemSprite* button_diamon_item = CCMenuItemSprite::create(button_diamon_nor,
																	button_diamon_sel,
																	button_diamon_disable,
																	this,
																	menu_selector(StoreLayer::menu_raffle_diamon_callback));
	CCSprite* text_diamon = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("raffle_diamond.png"));
	text_diamon->setPosition(ccp(button_diamon_nor->getContentSize().width/2,button_diamon_nor->getContentSize().height/2));
	button_diamon_item->addChild(text_diamon);
	//第一排菜单
	CCMenu* menu_row1 = CCMenu::create(button_friend_item,button_diamon_item,NULL);
	menu_row1->alignItemsHorizontallyWithPadding(30);
	menu_row1->setPosition(ccp(visibleSize.width/2,visibleSize.height/2+102));
	menu->addChild(menu_row1);
	//购买体力(金币)
	CCSprite* button_strengthbymoney_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* button_strengthbymoney_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* button_strengthbymoney_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	CCMenuItemSprite* button_strengthbymoney_item = CCMenuItemSprite::create(button_strengthbymoney_nor,
																			button_strengthbymoney_sel,
																			button_strengthbymoney_disable,
																			this,
																			menu_selector(StoreLayer::menu_buystrengthbymoney_callback));
	CCSprite* text_strengthbymoney = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_buy_str.png"));
	text_strengthbymoney->setPosition(ccp(button_strengthbymoney_nor->getContentSize().width/2,button_strengthbymoney_nor->getContentSize().height/2));
	button_strengthbymoney_item->addChild(text_strengthbymoney);
	//购买体力(符石)
	CCSprite* button_strengthbydiamon_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* button_strengthbydiamon_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* button_strengthbydiamon_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	CCMenuItemSprite* button_strengthbydiamon_item = CCMenuItemSprite::create(button_strengthbydiamon_nor,
		button_strengthbydiamon_sel,
		button_strengthbydiamon_disable,
		this,
		menu_selector(StoreLayer::menu_buystrengthbydiamon_callback));
	CCSprite* text_strengthbydiamon = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_buy_str.png"));
	text_strengthbydiamon->setPosition(ccp(button_strengthbydiamon_nor->getContentSize().width/2,button_strengthbydiamon_nor->getContentSize().height/2));
	button_strengthbydiamon_item->addChild(text_strengthbydiamon);
	//第二排菜单
	CCMenu* menu_row2 = CCMenu::create(button_strengthbymoney_item,button_strengthbydiamon_item,NULL);
	menu_row2->alignItemsHorizontallyWithPadding(30);
	menu_row2->setPosition(ccp(visibleSize.width/2,visibleSize.height/2-6));
	menu->addChild(menu_row2);
}
//友情抽奖 花少量金币 抽一张吞噬卡牌
void StoreLayer::menu_raffle_friend_callback(CCObject*)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	//判断金币是否充足
	if(Hero::sharedHero()->getMoney() < 50)
	{
		DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("store_friendraffle_tips"));
		this->addChild(layer);
		return;
	}
	//更新金币
	Hero::sharedHero()->setMoney(Hero::sharedHero()->getMoney() - 50);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMoneyAndDiamon");
	//更新卡牌
	int index = rand() % 6;
	CardTeam::sharedCardTeam()->setEatedCardCountByKey(index,1);
	CCScene* scene = RaffleOneLayer::scene(index);
	CCDirector::sharedDirector()->pushScene(scene);
}
//符石抽奖 花部分符石 连抽十次吞噬卡牌
void StoreLayer::menu_raffle_diamon_callback(CCObject*)
{
	
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	//判断符石是否充足
	if(Hero::sharedHero()->getDiamond() < 250)
	{
		DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("store_diamonraffle_tips"));
		this->addChild(layer);
		return;
	}
	//更新符石
	Hero::sharedHero()->setDiamond(Hero::sharedHero()->getDiamond() - 250);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMoneyAndDiamon");
	//更新卡牌
	static int cards[10];
	for(int i = 0; i < 10; ++i)
	{
		cards[i] = rand() % 6;
		CardTeam::sharedCardTeam()->setEatedCardCountByKey(cards[i],1);
	}
	CCScene* scene = RaffleTenLayer::scene(cards);
	CCDirector::sharedDirector()->pushScene(scene);
}

void StoreLayer::menu_buystrengthbymoney_callback(CCObject*)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	//判断金币是否充足
	if(Hero::sharedHero()->getMoney() < 200)
	{
		DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("store_buystrengthbymoney_tips"));
		this->addChild(layer);
		return;
	}
	//更新数据
	Hero::sharedHero()->setMoney(Hero::sharedHero()->getMoney() - 200);
	int strength = Hero::sharedHero()->getStrength() + 30;
	strength = strength > 100?100:strength;
	Hero::sharedHero()->setStrength(strength);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMoneyAndDiamon");
	CCNotificationCenter::sharedNotificationCenter()->postNotification("updateStrengthAndExp");
	DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("store_buystrengthbymoney"));
	this->addChild(layer);
}

void StoreLayer::menu_buystrengthbydiamon_callback(CCObject*)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	//判断符石是否充足
	if(Hero::sharedHero()->getDiamond() < 50)
	{
		DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("store_buystrengthbydiamon_tips"));
		this->addChild(layer);
		return;
	}
	//更新数据
	Hero::sharedHero()->setDiamond(Hero::sharedHero()->getDiamond() - 50);
	int strength = Hero::sharedHero()->getStrength() + 20;
	strength = strength > 100?100:strength;
	Hero::sharedHero()->setStrength(strength);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMoneyAndDiamon");
	CCNotificationCenter::sharedNotificationCenter()->postNotification("updateStrengthAndExp");
	DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("store_buystrengthbydiamon"));
	this->addChild(layer);
}


#include "MailLayer.h"
#include "AppMacros.h"
#include "AppStringFile.h"
#include "Hero.h"

bool MailLayer::init()
{
	if(!CCLayer::init())return false;
	initframe();
	addmail();
	return true;
}

void MailLayer::initframe()
{
	//背景
	CCSprite* background = CCSprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(ccp(visibleSize.width/2,760));
	this->addChild(background);
	//底部背景
	CCSprite* bottom_list = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bottom_list.jpg"));
	bottom_list->setPosition(ccp(visibleSize.width/2,bottom_list->getContentSize().height/2));
	this->addChild(bottom_list);
	//中间的背景
	CCSprite* listbase = CCSprite::create("ui/listbase_1.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(ccp(visibleSize.width/2,410));
	this->addChild(listbase);
	//顶部文字背景
	CCSprite* middletitlebase = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("middletitlebase.png"));
	middletitlebase->setPosition(ccp(visibleSize.width/2,700));
	this->addChild(middletitlebase);
	//顶部文字
	CCSprite* titlenamemycard = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("titlename_mail.png"));
	titlenamemycard->setPosition(ccp(visibleSize.width/2,690));
	this->addChild(titlenamemycard);
	//返回按钮
	CCSprite* button_left_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_0.png"));
	CCSprite* button_left_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_1.png"));
	CCSprite* button_left_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_2.png"));
	CCMenuItemSprite* button_left_item = CCMenuItemSprite::create(button_left_nor,
																	button_left_sel,
																	button_left_disable,
																	this,
																	menu_selector(MailLayer::menu_returncallback));
	CCSprite* text_return = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_return.png"));
	text_return->setPosition(ccp(button_left_nor->getContentSize().width/2-15,button_left_nor->getContentSize().height/2));
	button_left_item->addChild(text_return);
	CCMenu* button_left_menu = CCMenu::create(button_left_item,NULL);
	button_left_menu->setPosition(ccp(button_left_nor->getContentSize().width/2-10,687));
	this->addChild(button_left_menu);
	//金币奖励
	//单元格背景
	CCSprite* money_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_rank_elite_1.png"));
	CCSprite* money_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_rank_elite_1.png"));
	CCMenuItemSprite* moneyitem = CCMenuItemSprite::create(money_nor,money_sel,this,menu_selector(MailLayer::moneymenu_callback));
	img_h1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("listbutton_base1_1.png"));
	img_h1->setAnchorPoint(ccp(0,0));
	img_h1->setPosition(ccp(0,5));
	img_h1->setScale(1.4f);
	moneyitem->addChild(img_h1);
	//左边图片框
	CCSprite* money_frame =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class5.png"));
	money_frame->setAnchorPoint(ccp(0,0));
	money_frame->setPosition(ccp(20,10));
	money_frame->setScale(0.9f);
	moneyitem->addChild(money_frame);
	//左边图片
	CCSprite* money_img = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_bigcoin.png"));
	money_img->setPosition(ccp(15,5));
	money_img->setAnchorPoint(ccp(0,0));
	moneyitem->addChild(money_img);
	//中间文本
	CCLabelTTF* moneytittle = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey("mail_money_tittle"),"Arial",25);
	moneytittle->setAnchorPoint(ccp(0,0));
	moneytittle->setPosition(ccp(140,66));
	moneyitem->addChild(moneytittle);
	CCLabelTTF* moneytext = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey("mail_money_text"),"Arial",20);
	moneytext->setAnchorPoint(ccp(0,0));
	moneytext->setPosition(ccp(140,30));
	moneyitem->addChild(moneytext);
	//右边标志
	money_sign1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sign_underway.png"));
	money_sign1->setAnchorPoint(ccp(0,0));
	money_sign1->setPosition(ccp(420,25));
	moneyitem->addChild(money_sign1);
	money_sign2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sign_complete.png"));
	money_sign2->setAnchorPoint(ccp(0,0));
	money_sign2->setPosition(ccp(420,25));
	moneyitem->addChild(money_sign2);
	money_sign2->setVisible(false);
	moneymenu = CCMenu::create(moneyitem,NULL);
	this->addChild(moneymenu);
	moneymenu->setPosition(ccp(visibleSize.width/2,visibleSize.height/2+100));
	moneymenu->setVisible(false);
	//符石奖励
	//单元格背景
	CCSprite* diamon_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_rank_elite_1.png"));
	CCSprite* diamon_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_rank_elite_1.png"));
	CCMenuItemSprite* diamonitem = CCMenuItemSprite::create(diamon_nor,diamon_sel,this,menu_selector(MailLayer::diamonmenu_callback));
	img_h2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("listbutton_base1_1.png"));
	img_h2->setAnchorPoint(ccp(0,0));
	img_h2->setPosition(ccp(0,5));
	img_h2->setScale(1.4f);
	diamonitem->addChild(img_h2);
	//左边图片框
	CCSprite* diamon_frame =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class5.png"));
	diamon_frame->setAnchorPoint(ccp(0,0));
	diamon_frame->setPosition(ccp(20,10));
	diamon_frame->setScale(0.9f);
	diamonitem->addChild(diamon_frame);
	//左边图片
	CCSprite* diamon_img = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_diamond1.png"));
	diamon_img->setPosition(ccp(15,5));
	diamon_img->setAnchorPoint(ccp(0,0));
	diamonitem->addChild(diamon_img);
	//中间文本
	CCLabelTTF* diamontittle = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey("mail_diamon_tittle"),"Arial",25);
	diamontittle->setAnchorPoint(ccp(0,0));
	diamontittle->setPosition(ccp(140,66));
	diamonitem->addChild(diamontittle);
	CCLabelTTF* diamontext = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey("mail_diamon_text"),"Arial",20);
	diamontext->setAnchorPoint(ccp(0,0));
	diamontext->setPosition(ccp(140,30));
	diamonitem->addChild(diamontext);
	//右边标志
	diamon_sign1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sign_underway.png"));
	diamon_sign1->setAnchorPoint(ccp(0,0));
	diamon_sign1->setPosition(ccp(420,25));
	diamonitem->addChild(diamon_sign1);
	diamon_sign2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sign_complete.png"));
	diamon_sign2->setAnchorPoint(ccp(0,0));
	diamon_sign2->setPosition(ccp(420,25));
	diamonitem->addChild(diamon_sign2);
	diamon_sign2->setVisible(false);
	diamonmenu = CCMenu::create(diamonitem,NULL);
	this->addChild(diamonmenu);
	diamonmenu->setPosition(ccp(visibleSize.width/2,visibleSize.height/2-20));
	diamonmenu->setVisible(false);
}

//添加邮件
void MailLayer::addmail()
{
	time_t t = time(NULL);
	int sec = CCUserDefault::sharedUserDefault()->getIntegerForKey("systime_sec",0);
	if(sec == 0 || t - sec >= 20)
	{
		moneymenu->setVisible(true);
		diamonmenu->setVisible(true);
		//记录当前领取时间
		CCUserDefault::sharedUserDefault()->setIntegerForKey("systime_sec",t);
	}
}

void MailLayer::diamonmenu_callback(CCObject* psender)
{
	img_h2->setVisible(false);
	diamon_sign1->setVisible(false);
	diamon_sign2->setVisible(true);
	Hero::sharedHero()->setDiamond(Hero::sharedHero()->getDiamond() + 100);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMoneyAndDiamon");
}

void MailLayer::moneymenu_callback(CCObject*)
{
	img_h1->setVisible(false);
	money_sign1->setVisible(false);
	money_sign2->setVisible(true);
	Hero::sharedHero()->setMoney(Hero::sharedHero()->getMoney() + 500);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMoneyAndDiamon");
}

void MailLayer::menu_returncallback(CCObject*)
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification("ReturnToMain");
}


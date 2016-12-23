#include "BattleResultLayer.h"
#include "AppStringFile.h"
#include "AppMacros.h"
#include "Hero.h"
#include "CardTeam.h"

bool BattleResultLayer::init()
{
	if(!CCLayer::init())return false;
	for(int i = 0; i < 6; ++i)booty_card[i] = 0;
	//初始化战利品的坐标
	posy[0] = posy[1] = posy[2] = posy[3] = 250; posy[4] = 130;
	posx[0] = 100;
	posx[1] = 240;
	posx[2] = 380;
	posx[3] = 520;
	posx[4] = 100;
	srand(time(NULL));
	initBK();
	showbooty_card();
	this->setTouchEnabled(true);
	return true;
}

void BattleResultLayer::initBK()
{
	//关卡
	guanqia = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectedguanqia",0);
	int money = rand()%51 + guanqia * 50;//所得金币
	int diamon = rand()%41 + guanqia * 40;//所得符石
	int exp = rand()%31 + guanqia * 30;//所得经验
	//背景
	CCSprite* bk = CCSprite::create("ui/background_1.jpg");
	bk->setScale(2.23f);
	bk->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(bk);
	//标题
	CCSprite* titlename_fightcount = CCSprite::createWithSpriteFrameName("titlename_fightcount.png");
	titlename_fightcount->setPosition(ccp(visibleSize.width/2,700));
	this->addChild(titlename_fightcount);
	//关卡名
	CCString* str = CCString::createWithFormat("normal_instance_%02d",guanqia);
	CCLabelTTF* guanqia_name = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",35);
	guanqia_name->setColor(ccc3(255,255,0));
	guanqia_name->setAnchorPoint(ccp(0,0.5));
	guanqia_name->setPosition(ccp(60,630));
	this->addChild(guanqia_name);
	//难度
	CCLabelTTF* difficulty;
	if(guanqia <= 10)
	{
		str->initWithFormat("normal_difficulty");
		difficulty = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",28);
	}
	else
	{
		str->initWithFormat("elite_difficulty");
		difficulty = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",28);
	}
	difficulty->setColor(ccc3(255,255,0));
	difficulty->setAnchorPoint(ccp(1,0.5));
	difficulty->setPosition(ccp(visibleSize.width/2+200,550));
	this->addChild(difficulty);
	//获得金币
	CCLabelTTF* money_text = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey("battleResult_getmoney"),"Arial",28);
	money_text->setPosition(ccp(visibleSize.width/2-200,500));
	this->addChild(money_text);
	//金币值
	str->initWithFormat("%d",money);
	CCLabelTTF* money_value = CCLabelTTF::create(str->m_sString.c_str(),"Arial",28);
	money_value->setPosition(ccp(visibleSize.width/2+200,500));
	money_value->setAnchorPoint(ccp(1,0.5));
	this->addChild(money_value);
	//获得符石
	CCLabelTTF* diamon_text = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey("battleResult_getdiamon"),"Arial",28);
	diamon_text->setPosition(ccp(visibleSize.width/2-200,450));
	this->addChild(diamon_text);
	//符石值
	str->initWithFormat("%d",diamon);
	CCLabelTTF* diamon_value = CCLabelTTF::create(str->m_sString.c_str(),"Arial",28);
	diamon_value->setPosition(ccp(visibleSize.width/2+200,450));
	diamon_value->setAnchorPoint(ccp(1,0.5));
	this->addChild(diamon_value);
	//获得经验
	CCLabelTTF* exp_text = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey("battleResult_getexp"),"Arial",28);
	exp_text->setPosition(ccp(visibleSize.width/2-200,400));
	this->addChild(exp_text);
	//符石值
	str->initWithFormat("%d",exp);
	CCLabelTTF* exp_value = CCLabelTTF::create(str->m_sString.c_str(),"Arial",28);
	exp_value->setPosition(ccp(visibleSize.width/2+200,400));
	exp_value->setAnchorPoint(ccp(1,0.5));
	this->addChild(exp_value);
	//战利品
	CCSprite* text_booty = CCSprite::createWithSpriteFrameName("text_booty.png");
	text_booty->setPosition(ccp(visibleSize.width/2,350));
	this->addChild(text_booty);
	//更新数据
	Hero::sharedHero()->setMoney(Hero::sharedHero()->getMoney() + money);
	Hero::sharedHero()->setDiamond(Hero::sharedHero()->getDiamond() + diamon);
	Hero::sharedHero()->setExp(Hero::sharedHero()->getExp() + exp);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMoneyAndDiamon");
	CCNotificationCenter::sharedNotificationCenter()->postNotification("updateStrengthAndExp");
}

void BattleResultLayer::showbooty_card()
{
	int index = 0;//记录坐标
	//抽的次数
	int sum = guanqia / 3 + 3;
	for(int i = 0; i < sum; ++i)
	{
		booty_card[rand()%6]++;
	}
	for(int i = 0; i < 6; ++i)
	{
		if(booty_card[i])
		{
			//数据的更新
			CardTeam::sharedCardTeam()->setEatedCardCountByKey(i,booty_card[i]);
			CCString* str = CCString::createWithFormat("eatedcard%d",i);
			CCSprite* card = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString));
			this->addChild(card);
			card->setPosition(ccp(posx[index],posy[index]));
			CCSprite* frame = CCSprite::createWithSpriteFrameName("littlecard_frame_class1.png");
			this->addChild(frame);
			frame->setPosition(ccp(posx[index],posy[index]));
			frame->setOpacity(0);
			str->initWithFormat("X%d",booty_card[i]);
			CCLabelTTF* count = CCLabelTTF::create(str->m_sString.c_str(),"Arial",23);
			count->setColor(ccc3(255,0,0));
			card->addChild(count);
			count->setAnchorPoint(ccp(0,1));
			count->setPosition(ccp(4,card->getContentSize().height-4));
			card->setOpacity(0);
			card->runAction(CCFadeIn::create(1.5f));
			frame->runAction(CCFadeIn::create(1.5f));
			index++;
		}
	}
}

void BattleResultLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool BattleResultLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void BattleResultLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	this->removeFromParent();
}


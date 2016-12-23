#include "MainUIScene.h"
#include "AppMacros.h"
#include "Hero.h"
#include "ValueConvert.h"
#include "AppStringFile.h"
#include "MainTopUITouchLayer.h"

bool MainUIScene::init()
{
	if(!CCScene::init())return false;
	mainuilayer = NULL;
	multilayer = NULL;
	configureMultiplexLayer();
	configureTopUI();
	configureButtonUI();
	initSysInfoLayer();
	scrollText();
	//添加显示战斗结果的监听
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(MainUIScene::show_BattleResult),"showBatleResult",NULL);
	//添加更新金币和符石的监听
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(MainUIScene::updateMoneyAndDiamon),"updateMoneyAndDiamon",NULL);
	//添加更新体力和经验的监听
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(MainUIScene::updateStrengthAndExp),"updateStrengthAndExp",NULL);

	return true;
}

void MainUIScene::button_Homepage(CCObject*)
{
	multilayer->switchTo(0);
	mainuilayer->restoreToMainUI();
}

void MainUIScene::button_Instance(CCObject*)
{
	//multilayer->switchTo(1);
}

void MainUIScene::button_Fight(CCObject*)
{
	//multilayer->switchTo(2);
}

void MainUIScene::button_Store(CCObject*)
{
	//multilayer->switchTo(3);
}

void MainUIScene::button_More(CCObject*)
{
	//multilayer->switchTo(4);
}
//添加顶部触摸层
void MainUIScene::initSysInfoLayer()
{
	MainTopUITouchLayer* layer = MainTopUITouchLayer::create();
	this->addChild(layer,6);
}
//底部选项的切换
void MainUIScene::configureMultiplexLayer()
{
	mainuilayer = MainUILayer::create();
	multilayer = CCLayerMultiplex::create(mainuilayer,NULL);
	this->addChild(multilayer,1);
}
//顶部UI设计
void MainUIScene::configureTopUI()
{
	//顶部的状态
	CCSprite* top = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("top.png"));
	top->setPosition(ccp(visibleSize.width/2,visibleSize.height-top->getContentSize().height/2));
	this->addChild(top,5);
	top->setTag(MAIN_TOP);
	//爵位
	CCString* str = CCString::createWithFormat("rank_%d.png",Hero::sharedHero()->getRank());
	rank = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->m_sString.c_str()));
	rank->setPosition(ccp(35,top->getContentSize().height-27));
	top->addChild(rank);
    //名字
	CCLabelTTF* playername = CCLabelTTF::create(Hero::sharedHero()->getName_().c_str(),"Arial",25);
	playername->setColor(ccc3(139,0,255));
	playername->setPosition(ccp(130,top->getContentSize().height-27));
	top->addChild(playername);
	//等级
	CCSprite* textlv = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("info_lv.png"));
	textlv->setPosition(ccp(335,top->getContentSize().height-38));
	top->addChild(textlv);
	lv = CCLabelTTF::create(ValueConvert::intToChar(*str,Hero::sharedHero()->getLevel_()),"Arial",25);
	lv->setAnchorPoint(ccp(0,0.5));
	lv->setColor(ccc3(255,255,0));
	lv->setPosition(ccp(388,top->getContentSize().height-37));
	top->addChild(lv);
	//符石
	diamond = CCLabelTTF::create(ValueConvert::intToChar(*str,Hero::sharedHero()->getDiamond()),"Arial",32);
	diamond->setAnchorPoint(ccp(1,0.5));
	diamond->setColor(ccc3(0,255,0));
	diamond->setPosition(ccp(620,top->getContentSize().height-50));
	top->addChild(diamond);
	//金币
	money = CCLabelTTF::create(ValueConvert::intToChar(*str,Hero::sharedHero()->getMoney()),"Arial",32);
	money->setAnchorPoint(ccp(1,0.5));
	money->setColor(ccc3(255,255,0));
	money->setPosition(ccp(620,top->getContentSize().height-110));
	top->addChild(money);
	//经验条
	CCSprite* exp = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("info_exp.png"));
	exp->setPosition(ccp(52,113));
	top->addChild(exp);
	CCSprite* expbackgroup = CCSprite::create("ui/exp_0.png");
	expbackgroup->setScale(2.8f);
	expbackgroup->setPosition(ccp(260,113));
	top->addChild(expbackgroup);
	CCProgressTimer* exp2 = CCProgressTimer::create(CCSprite::create("ui/exp_1.png"));
	exp2->setScale(2.8f);
	exp2->setPosition(ccp(260,115));
	exp2->setBarChangeRate(ccp(1,0));//（1,0）表示横方向
	exp2->setType(kCCProgressTimerTypeBar);//设置进度条为水平
	exp2->setMidpoint(ccp(0,0));//设置进度条从左到右 从0开始
	exp2->setTag(MAIN_TOP_EXP);
	exp2->setPercentage(Hero::sharedHero()->getExp());
	top->addChild(exp2);
	//体力槽
	CCSprite* strength = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("info_strength.png"));
	strength->setPosition(ccp(50,68));
	top->addChild(strength);
	CCSprite* strengthbackgroup = CCSprite::create("ui/strength_0.png");
	strengthbackgroup->setScale(2.3f);
	strengthbackgroup->setPosition(ccp(230,60));
	top->addChild(strengthbackgroup);
	CCProgressTimer* strength2 = CCProgressTimer::create(CCSprite::create("ui/strength_1.png"));
	strength2->setScale(2.3f);
	strength2->setPosition(ccp(230,60));
	//设置进度条长度和高度开始变化的大小
	strength2->setBarChangeRate(ccp(1,0));//（1,0）表示横方向
	strength2->setType(kCCProgressTimerTypeBar);//设置进度条为水平
	strength2->setMidpoint(ccp(0,0));//设置进度条从左到右 从0开始
	strength2->setPercentage(Hero::sharedHero()->getStrength());
	top->addChild(strength2);
	strength2->setTag(MAIN_TOP_STRENGTH_PROGERESS);

	//时间 和 体力值
	CCLabelTTF* texttime = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey("timetext"),"Arial",25);
	texttime->setPosition(ccp(120,77));
	top->addChild(texttime);
	CCLabelTTF* time = CCLabelTTF::create("00:10","Arial",25);
	time->setPosition(ccp(210,77));
	top->addChild(time);
	time->setTag(MAIN_TOP_STRENGTH_TIME);
	str->initWithFormat("%d/100",Hero::sharedHero()->getStrength());
	CCLabelTTF* strengthvalue = CCLabelTTF::create(str->getCString(),"Arial",25);
	strengthvalue->setPosition(ccp(320,77));
	top->addChild(strengthvalue);
	strengthvalue->setTag(MAIN_TOP_STRENGTH_VALUE);
	this->schedule(schedule_selector(MainUIScene::updateStrengthTime),1.0f);
}
//底部UI设计
void MainUIScene::configureButtonUI()
{
	//主页
	CCSprite* button_homepage_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_homepage_0.png"));
	CCSprite* button_homepage_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_homepage_1.png"));
	CCSprite* button_homepage_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_homepage_2.png"));
	CCMenuItemSprite * homepageitemspr = CCMenuItemSprite::create(button_homepage_nor,
		                                                      button_homepage_sel,
															  button_homepage_disable,
															  this,
															  menu_selector(MainUIScene::button_Homepage));
	homepageitemspr->setScale(1.1f);
	//副本
	CCSprite* button_instance_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_instance_0.png"));
	CCSprite* button_instance_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_instance_1.png"));
	CCSprite* button_instance_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_instance_2.png"));
	CCMenuItemSprite * instanceitemspr = CCMenuItemSprite::create(button_instance_nor,
															     button_instance_sel,
															     button_instance_disable,
															     this,
															     menu_selector(MainUIScene::button_Instance));
	instanceitemspr->setScale(1.1f);
	//战斗
	CCSprite* button_fight_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_fight_0.png"));
	CCSprite* button_fight_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_fight_1.png"));
	CCSprite* button_fight_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_fight_2.png"));
	CCMenuItemSprite * fightitemspr = CCMenuItemSprite::create(button_fight_nor,
																button_fight_sel,
																button_fight_disable,
																this,
																menu_selector(MainUIScene::button_Fight));
	fightitemspr->setScale(1.1f);
	//商店
	CCSprite* button_store_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_store_0.png"));
	CCSprite* button_store_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_store_1.png"));
	CCSprite* button_store_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_store_2.png"));
	CCMenuItemSprite * storeitemspr = CCMenuItemSprite::create(button_store_nor,
																button_store_sel,
																button_store_disable,
																this,
																menu_selector(MainUIScene::button_Store));
	storeitemspr->setScale(1.1f);
	//攻略
	CCSprite* button_more_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_more_0.png"));
	CCSprite* button_more_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_more_1.png"));
	CCSprite* button_more_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_more_2.png"));
	CCMenuItemSprite * moreitemspr = CCMenuItemSprite::create(button_more_nor,
																button_more_sel,
																button_more_disable,
																this,
																menu_selector(MainUIScene::button_More));
	moreitemspr->setScale(1.1f);
	//底部菜单
	CCMenu* mainmenu = CCMenu::create(homepageitemspr,instanceitemspr,fightitemspr,storeitemspr,moreitemspr,NULL);
	mainmenu->alignItemsHorizontallyWithPadding(-10);
	mainmenu->setPosition(ccp(visibleSize.width/2,button_homepage_nor->getContentSize().height/2-5));
	this->addChild(mainmenu,2);

}
//系统公告
void MainUIScene::scrollText()
{
	text = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey("Game_Gonggao"),"Arial",28);
	text->setPosition(ccp(visibleSize.width + text->getContentSize().width/2,125));
	text->setColor(ccc3(255,255,0));
	this->addChild(text,3);
	this->scheduleUpdate();//开启定时器
}

void MainUIScene::show_BattleResult(CCObject*)
{

}

void MainUIScene::updateMoneyAndDiamon(CCObject*)
{
	CCString* str = CCString::create("");
	money->setString(ValueConvert::intToChar(*str,Hero::sharedHero()->getMoney()));
	diamond->setString(ValueConvert::intToChar(*str,Hero::sharedHero()->getDiamond()));
}

void MainUIScene::updateStrengthAndExp(CCObject*)
{
	CCString* str = CCString::create("");
	//更新经验条
	CCSprite* maintop = (CCSprite*)getChildByTag(MAIN_TOP);
	CCProgressTimer* exp = (CCProgressTimer*)maintop->getChildByTag(MAIN_TOP_EXP);
	if(Hero::sharedHero()->getExp() >= Hero::sharedHero()->getCurLevelMaxExp())//能升级
	{
		//计算能升几个等级
		int i = getUpLevel(Hero::sharedHero()->getExp(),Hero::sharedHero()->getCurLevelMaxExp());
		Hero::sharedHero()->setLevel_(Hero::sharedHero()->getLevel_() + i);
		str->initWithFormat("%d",Hero::sharedHero()->getLevel_());
		lv->setString(str->m_sString.c_str());
		//更新最大经验值
		Hero::sharedHero()->setCurLevelMaxExp(100*Hero::sharedHero()->getLevel_());
		//更新军衔
		CCSprite* top = (CCSprite*)getChildByTag(MAIN_TOP);
		Hero::sharedHero()->setRank(Hero::sharedHero()->getLevel_()/3+1);
		rank->removeFromParent();
		str->initWithFormat("rank_%d.png",Hero::sharedHero()->getRank());
		rank = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->m_sString.c_str()));
		rank->setPosition(ccp(35,top->getContentSize().height-27));
		top->addChild(rank);
		//弹出升级模态对话框
		//......
	}
	exp->setPercentage((100.0*Hero::sharedHero()->getExp())/Hero::sharedHero()->getCurLevelMaxExp());
	//更新体力值和体力条
	str->initWithFormat("%d/100",Hero::sharedHero()->getStrength());
	CCLabelTTF* strength = (CCLabelTTF*)maintop->getChildByTag(MAIN_TOP_STRENGTH_VALUE);
	strength->setString(str->m_sString.c_str());
	//进度条
	CCProgressTimer* progress = (CCProgressTimer*)maintop->getChildByTag(MAIN_TOP_STRENGTH_PROGERESS);
	progress->setPercentage(Hero::sharedHero()->getStrength());
}

void MainUIScene::update(float)
{
	int x = text->getPositionX() - 1;
	if(x < -text->getContentSize().width/2)
	{
		x = visibleSize.width + text->getContentSize().width/2;
	}
	text->setPositionX(x);
}

void MainUIScene::updateStrengthTime(float)
{
	CCSprite* maintop = (CCSprite*)getChildByTag(MAIN_TOP);
	string str = ((CCLabelTTF*)(maintop->getChildByTag(MAIN_TOP_STRENGTH_TIME)))->getString();
	((CCLabelTTF*)(maintop->getChildByTag(MAIN_TOP_STRENGTH_TIME)))->setString(getStrengthTime(str).c_str());
}

string MainUIScene::getStrengthTime(string curtime)
{
	string strmin(curtime,0,2);//取出分
	int min = atoi(strmin.c_str());
	string strsec(curtime,3,2);//取出秒
	int sec = atoi(strsec.c_str());
	if(--sec<0)
	{
		sec = 59;
		if(--min<0)
		{
			min = 4;
			//当倒计时完后 更新体力值和进度条
			CCSprite* maintop = (CCSprite*)getChildByTag(MAIN_TOP);
			int curstrength = Hero::sharedHero()->getStrength() + 5;
			curstrength = curstrength > 100?100:curstrength;
			Hero::sharedHero()->setStrength(curstrength);
			CCString* str = CCString::createWithFormat("%d/100",curstrength);
			((CCLabelTTF*)(maintop->getChildByTag(MAIN_TOP_STRENGTH_VALUE)))->setString(str->m_sString.c_str());
			//进度条
			CCProgressTimer* progress = (CCProgressTimer*)maintop->getChildByTag(MAIN_TOP_STRENGTH_PROGERESS);
			progress->setPercentage(curstrength);
		}
	}
	CCString str;
	str.initWithFormat("%02d:%02d",min,sec);
	return str.m_sString;
}

int MainUIScene::getUpLevel(int exp,int curmaxexp)
{
	int i = 0;
	while(exp >= curmaxexp)
	{
		i++;
		exp = exp - curmaxexp;
		curmaxexp += 100;
	}
	Hero::sharedHero()->setExp(exp);
	return i;
}


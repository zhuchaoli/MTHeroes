#include "BattleLayer.h"
#include "AppMacros.h"
#include "AppStringFile.h"
#include "CardTeam.h"
#include "Hero.h"
#include "GuanQiaState.h"

CCScene* BattleLayer::scene()
{
	CCScene* scene = CCScene::create();
	BattleLayer* layer = BattleLayer::create();
	scene->addChild(layer);
	return scene;
}

bool BattleLayer::init()
{
	if(!CCLayer::init())return false;
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/battle_backgroundmusic1.mp3",true);
	curGuanQia = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectedguanqia",0);
	m_curSpeed = SPEED_X1;
	m_isShowGoAhead = false;
	m_curPlay = FIRST;
	pos_hero_x[0] = pos_hero_x[3] = 150;
	pos_hero_x[2] = pos_hero_x[4] = 490;
	pos_hero_x[1] = 320;
	pos_hero_y[0] = pos_hero_y[1] = pos_hero_y[2] = 340; 
	pos_hero_y[3] = pos_hero_y[4] = 140; 

	pos_monster_x[0] = pos_monster_x[3] = 150;
	pos_monster_x[1] = pos_monster_x[4] = 320;
	pos_monster_x[2] = pos_monster_x[5] = 490;
	pos_monster_y[0] = pos_monster_y[1] = pos_monster_y[2] = 820;
	pos_monster_y[3] = pos_monster_y[4] = pos_monster_y[5] = 620;
	pos_monster_x[6] = pos_monster_x[8] = 150;
	pos_monster_x[7] = pos_monster_x[9] = 490;
	pos_monster_x[10] = 320;
	pos_monster_y[6] = pos_monster_y[7] = 820;
	pos_monster_y[8] = pos_monster_y[9] = 620;
	pos_monster_y[10] = 720;
	//初始化英雄的生命和攻击
	for(int i = 0; i < 5; ++i)
	{
		hero_life[i] = CardTeam::sharedCardTeam()->getLifeByKey(i);
		hero_attack[i] = CardTeam::sharedCardTeam()->getAttackByKey(i);
	}
	initMonsterLifeAndAttack();
	initMonsterOrder();
	initBk();
	initContent();
	initSkillAnimation();
	srand(time(NULL));
	//初始化英雄和怪物活着的
	for(int i = 0; i < 5; ++i)hero_alive.push_back(i);
	for(int i = 0; i < 6; ++i)monster_alive.push_back(i);
	//显示战斗
	showText(0);
	this->scheduleOnce(schedule_selector(BattleLayer::first_hero_play),2.0f);
	this->setTouchEnabled(true);
	return true;
}

void BattleLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool BattleLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void BattleLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pt = pTouch->getLocationInView();//屏幕坐标
	pt = CCDirector::sharedDirector()->convertToGL(pt);//转换成世界坐标
	CCRect goahead_rect = CCRectMake(goahead->getPositionX()-goahead->getContentSize().width/2,
		                             goahead->getPositionY()-goahead->getContentSize().height/2,
									 goahead->getContentSize().width,
									 goahead->getContentSize().height);
	//判断是否点中速度
	if(pt.x < 100 && pt.y < 80)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
		switch(m_curSpeed)
		{
		case SPEED_X1:
			m_curSpeed = SPEED_X2;
			speed[0]->setVisible(false);
			speed[2]->setVisible(false);
			speed[1]->setVisible(true);
			CCDirector::sharedDirector()->getScheduler()->setTimeScale(2.0f);
			break;
		case SPEED_X2:
			m_curSpeed = SPEED_X3;
			speed[0]->setVisible(false);
			speed[1]->setVisible(false);
			speed[2]->setVisible(true);
			CCDirector::sharedDirector()->getScheduler()->setTimeScale(3.0f);
			break;
		case SPEED_X3:
			m_curSpeed = SPEED_X1;
			speed[1]->setVisible(false);
			speed[2]->setVisible(false);
			speed[0]->setVisible(true);
			CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0f);
			break;
		}
	}
	else if(m_isShowGoAhead	&& goahead_rect.containsPoint(pt))
	{
		SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
		goahead->stopAllActions();
		goahead->setVisible(false);
		m_isShowGoAhead = false;
		if(m_curPlay == FIRST)
		{
			m_curPlay = SECOND;
			//初始化怪物活着的
			for(int i = 0; i < 6; ++i)monster_alive.push_back(i);
			//怪物加满血
			initMonsterLifeAndAttack();
			bkmovecount = 1;
			runBK();
			runCard();
			runcardshake();
			scheduleOnce(schedule_selector(BattleLayer::show_allmonster),1.4f);
			scheduleOnce(schedule_selector(BattleLayer::second_hero_play),1.7f);
		}
		else if(m_curPlay == SECOND)
		{
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/battle_backgroundmusic2.mp3",true);
			m_curPlay = THIRD;
			bk_3->setVisible(true);
			//初始化怪物活着的
			for(int i = 6; i < 11; ++i)monster_alive.push_back(i);
			bkmovecount = 2;
			runBK();
			runCard();
			runcardshake();
			scheduleOnce(schedule_selector(BattleLayer::show_allmonster),1.4f);
			scheduleOnce(schedule_selector(BattleLayer::showText),1.4f);//显示boss
			scheduleOnce(schedule_selector(BattleLayer::third_hero_play),2.5f);
		}
	}
}
//加载背景
void BattleLayer::initBk()
{
	//背景
	bk_1 = CCSprite::create("ui/fightground_chengqiang.jpg");
	bk_1->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(bk_1);
	bk_2 = CCSprite::create("ui/fightground_chengqiang.jpg");
	bk_2->setPosition(ccp(visibleSize.width/2,visibleSize.height/2*3));
	this->addChild(bk_2);
	bk_3 = CCSprite::create("ui/fightground_chengqiang_EndPos.png");
	bk_3->setPosition(ccp(visibleSize.width/2,visibleSize.height-bk_3->getContentSize().height/2));
	bk_2->addChild(bk_3);
	bk_3->setVisible(false);
	//左下角的速度
	for(int i = 0; i < 3; ++i)
	{
		CCString* str = CCString::createWithFormat("speedx%d.png",i+1);
		speed[i] = CCSprite::createWithSpriteFrameName(str->m_sString.c_str());
		speed[i]->setPosition(ccp(45,40));
		this->addChild(speed[i]);
	}
	speed[1]->setVisible(false);
	speed[2]->setVisible(false);
	//前进的标志
	goahead = CCSprite::createWithSpriteFrameName("fight_goahead.png");
	goahead->setPosition(ccp(visibleSize.width/2,visibleSize.height/2+200));
	this->addChild(goahead);
	goahead->setVisible(false);
}
//加载卡牌
void BattleLayer::initContent()
{
	//加载英雄卡牌
	//队长
	hero[0] = CCNode::create();
	CCSprite* cardcap_frame = CCSprite::createWithSpriteFrameName("bigcard_frame_class4_elite.png");
	hero[0]->addChild(cardcap_frame);
	CCString* str = CCString::createWithFormat("captain_role_big");
	CCSprite* cardcap_content = CCSprite::createWithSpriteFrameName(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString));
	hero[0]->addChild(cardcap_content);
	CCSprite* cardcap_occupation_base = CCSprite::createWithSpriteFrameName("icon_occupation_base_elite.png");
	hero[0]->addChild(cardcap_occupation_base);
	CCSprite* cardcap_occupation = CCSprite::createWithSpriteFrameName("icon_occupation_warrior_button.png");
	cardcap_occupation->setScale(2.0f);
	cardcap_occupation->setPosition(ccp(61,-73));
	hero[0]->addChild(cardcap_occupation);
	hero[0]->setScale(0.7f);
	hero[0]->setPosition(ccp(pos_hero_x[0],pos_hero_y[0]));
	this->addChild(hero[0]);
	//队员
	for(int i = 1; i < 5; ++i)
	{
		hero[i] = CCNode::create();
		CCSprite* card_frame = CCSprite::createWithSpriteFrameName("bigcard_frame_class4_elite.png");
		hero[i]->addChild(card_frame);
		str->initWithFormat("teammate%d_role_big",i);
		CCSprite* card_content = CCSprite::createWithSpriteFrameName(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString));
		hero[i]->addChild(card_content);
		CCSprite* card_occupation_base = CCSprite::createWithSpriteFrameName("icon_occupation_base_elite.png");
		hero[i]->addChild(card_occupation_base);
		CCSprite* card_occupation = CCSprite::createWithSpriteFrameName("icon_occupation_shaman_button.png");
		card_occupation->setScale(2.0f);
		card_occupation->setPosition(ccp(61,-73));
		hero[i]->addChild(card_occupation);
		hero[i]->setScale(0.7f);
		hero[i]->setPosition(ccp(pos_hero_x[i],pos_hero_y[i]));
		this->addChild(hero[i]);
	}
	//加载怪物(第一波 第二波)
	for(int i = 0; i < 6; ++i)
	{
		monster[i] = CCNode::create();
		CCSprite* card_frame = CCSprite::createWithSpriteFrameName("bigcard_frame_class2.png");
		monster[i]->addChild(card_frame);
		str->initWithFormat("monster%d",monster_order[i]);
		CCSprite* card_content = CCSprite::createWithSpriteFrameName(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString));
		monster[i]->addChild(card_content);
		CCSprite* card_occupation = CCSprite::createWithSpriteFrameName("icon_occupation_mage_button.png");
		card_occupation->setScale(2.0f);
		card_occupation->setPosition(ccp(61,-73));
		monster[i]->addChild(card_occupation);
		monster[i]->setScale(0.7f);
		monster[i]->setPosition(ccp(pos_monster_x[i],pos_monster_y[i]));
		this->addChild(monster[i]);
	}
	//第三波
	for(int i = 6; i < 11; ++i)
	{
		monster[i] = CCNode::create();
		CCSprite* card_frame = CCSprite::createWithSpriteFrameName("bigcard_frame_class3.png");
		monster[i]->addChild(card_frame);
		str->initWithFormat("monster%d",monster_order[i]);
		CCSprite* card_content = CCSprite::createWithSpriteFrameName(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString));
		monster[i]->addChild(card_content);
		CCSprite* card_occupation = CCSprite::createWithSpriteFrameName("icon_occupation_mage_button.png");
		card_occupation->setScale(2.0f);
		card_occupation->setPosition(ccp(61,-73));
		monster[i]->addChild(card_occupation);
		if(i == 10) monster[i]->setScale(0.9f);
		else monster[i]->setScale(0.7f);
		monster[i]->setPosition(ccp(pos_monster_x[i],pos_monster_y[i]));
		this->addChild(monster[i]);
		monster[i]->setVisible(false);
	}
}
//将动画存入动画缓存
void BattleLayer::initSkillAnimation()
{
	CCAnimation* thunder_skill = CCAnimation::create();
	thunder_skill->setDelayPerUnit(0.1f);
	thunder_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("thunder_dian.png"));
	thunder_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("thunder_hua01.png"));
	thunder_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("thunder_hua02.png"));
	thunder_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("thunder_hua03.png"));
	thunder_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("thunder_hua04.png"));
	CCAnimationCache::sharedAnimationCache()->addAnimation(thunder_skill,"thunder_skill");

	CCAnimation* rock_skill = CCAnimation::create();
	rock_skill->setDelayPerUnit(0.1f);
	rock_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("thunder_shandian.png"));
	rock_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("thunder_shisui01.png"));
	rock_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("thunder_shisui02.png"));
	rock_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("thunder_shisui03.png"));
	CCAnimationCache::sharedAnimationCache()->addAnimation(rock_skill,"rock_skill");

	CCAnimation* windhit_skill = CCAnimation::create();
	windhit_skill->setDelayPerUnit(0.1f);
	windhit_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("windhit_01.png"));
	windhit_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("windhit_02.png"));
	windhit_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("windhit_03.png"));
	windhit_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("windhit_04.png"));
	windhit_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("windhit_05.png"));
	windhit_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("windhit_06.png"));
	CCAnimationCache::sharedAnimationCache()->addAnimation(windhit_skill,"windhit_skill");

	CCAnimation* zhongji_skill = CCAnimation::create();
	zhongji_skill->setDelayPerUnit(0.1f);
	zhongji_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("zhongji_shan0001.png"));
	zhongji_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("zhongji_shan0005.png"));
	zhongji_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("zhongji_shan0007.png"));
	CCAnimationCache::sharedAnimationCache()->addAnimation(zhongji_skill,"zhongji_skill");

	CCAnimation* tenarmy_skill = CCAnimation::create();
	tenarmy_skill->setDelayPerUnit(0.1f);
	tenarmy_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tenarmy_01.png"));
	tenarmy_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tenarmy_02.png"));
	tenarmy_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tenarmy_03.png"));
	tenarmy_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tenarmy_05.png"));
	tenarmy_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tenarmy_07.png"));
	tenarmy_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tenarmy_09.png"));
	tenarmy_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tenarmy_11.png"));
	tenarmy_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tenarmy_13.png"));
	tenarmy_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tenarmy_15.png"));
	tenarmy_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tenarmy_19.png"));
	CCAnimationCache::sharedAnimationCache()->addAnimation(tenarmy_skill,"tenarmy_skill");

	CCAnimation* blizzard_skill = CCAnimation::create();
	blizzard_skill->setDelayPerUnit(0.1f);
	blizzard_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blizzard_0001.png"));
	blizzard_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blizzard_0002.png"));
	blizzard_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blizzard_0003.png"));
	blizzard_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blizzard_0004.png"));
	blizzard_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blizzard_0005.png"));
	blizzard_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blizzard_0007.png"));
	blizzard_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blizzard_0008.png"));
	blizzard_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blizzard_0009.png"));
	blizzard_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blizzard_0010.png"));
	blizzard_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blizzard_0011.png"));
	CCAnimationCache::sharedAnimationCache()->addAnimation(blizzard_skill,"blizzard_skill");

	CCAnimation* customattack_skill = CCAnimation::create();
	customattack_skill->setDelayPerUnit(0.1f);
	customattack_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("attack0002.png"));
	customattack_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("attack0004.png"));
	customattack_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("attack0005.png"));
	customattack_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("attack0007.png"));
	customattack_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("attack0009.png"));
	customattack_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("attack0011.png"));
	CCAnimationCache::sharedAnimationCache()->addAnimation(customattack_skill,"customattack_skill");

	CCAnimation* heal_skill = CCAnimation::create();
	heal_skill->setDelayPerUnit(0.1f);
	heal_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("heal_1.png"));
	heal_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("heal_2.png"));
	heal_skill->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("heal_3.png"));
	CCAnimationCache::sharedAnimationCache()->addAnimation(heal_skill,"heal_skill");
}
//初始化怪物生命和攻击
void BattleLayer::initMonsterLifeAndAttack()
{
	int monsterlife[] = {100,120,130,150,170,190,250,260,270,280,300};
	int monsterattack[] = {50,60,55,65,70,75,100,105,110,115,120};
	for(int i = 0; i < 11; ++i)
	{
		monster_life[i] = monsterlife[i] + curGuanQia * 200;
		monster_attack[i] = monsterattack[i] + curGuanQia * 150;
	}
}
//初始化怪物的队形
void BattleLayer::initMonsterOrder()
{
	char pOrder[30] = {0};
	char *pstr;
	CCString* str = CCString::createWithFormat("gq%d_order",curGuanQia);
	const char* order = AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString);
	int len = strlen(order);
	for(int i = 0; i <= len; ++i)pOrder[i] = order[i];
	pstr = strtok(pOrder,",");
	monster_order[0] = atoi(pstr);
	for(int i = 1; i <= 10; ++i)
	{
		pstr = strtok(NULL,",");
		monster_order[i] = atoi(pstr);
	}
}
//第一幕英雄打
void BattleLayer::first_hero_play(float)
{
	gongjifang = true;
	//判断英雄是否死了
	int heroalivesum = hero_alive.size();
	if(heroalivesum == 0)//英雄已死
	{
		this->stopAllActions();
		this->unscheduleAllSelectors();
		//弹出战斗失败
		showFail();
		return;
	}
	//选择英雄
	int pos = hero_alive[rand() % heroalivesum];
	//选择怪物
	int dst = monster_alive[rand() % monster_alive.size()];
	switch (pos)
	{
	case 0:
		hero_0_skill(pos,dst);
		break;
	case 1:
		hero_1_skill(pos,dst);
		break;
	case 2:
		hero_2_skill(pos,dst);
		break;
	case 3:
		hero_3_skill(pos,dst);
		break;
	case 4:
		hero_4_skill(pos,dst);
		break;
	}
	this->scheduleOnce(schedule_selector(BattleLayer::first_monster_play),1.7f);
}

//第一波怪物打
void BattleLayer::first_monster_play(float)
{
	gongjifang = false;
	//判断怪物是否死了
	int monsteralivesum = monster_alive.size();
	if(monsteralivesum == 0)//怪物已死
	{
		this->stopAllActions();
		this->unscheduleAllSelectors();
		//进入第二幕 前进
		show_goahead();
		return;
	}
	//选择怪物
	int pos = monster_alive[rand() % monsteralivesum];     
	//选择英雄
	int dst = hero_alive[rand() % hero_alive.size()];
	switch (pos)
	{
	case 0:
		monster_0_skill(pos,dst);
		break;
	case 1:
		monster_1_skill(pos,dst);
		break;
	case 2:
		monster_2_skill(pos,dst);
		break;
	case 3:
		monster_3_skill(pos,dst);
		break;
	case 4:
		monster_4_skill(pos,dst);
		break;
	case 5:
		monster_5_skill(pos,dst);
		break;
	}
	this->scheduleOnce(schedule_selector(BattleLayer::first_hero_play),1.7f);
}
//第二幕英雄打
void BattleLayer::second_hero_play(float)
{
	gongjifang = true;
	//判断英雄是否死了
	int heroalivesum = hero_alive.size();
	if(heroalivesum == 0)//英雄已死
	{
		this->stopAllActions();
		this->unscheduleAllSelectors();
		//弹出战斗失败
		showFail();
		return;
	}
	//选择英雄
	int pos = hero_alive[rand() % heroalivesum];
	//选择怪物
	int dst = monster_alive[rand() % monster_alive.size()];
	switch (pos)
	{
	case 0:
		hero_0_skill(pos,dst);
		break;
	case 1:
		hero_1_skill(pos,dst);
		break;
	case 2:
		hero_2_skill(pos,dst);
		break;
	case 3:
		hero_3_skill(pos,dst);
		break;
	case 4:
		hero_4_skill(pos,dst);
		break;
	}
	this->scheduleOnce(schedule_selector(BattleLayer::second_monster_play),1.7f);
}
//第二波怪物打
void BattleLayer::second_monster_play(float)
{
	gongjifang = false;
	//判断怪物是否死了
	int monsteralivesum = monster_alive.size();
	if(monsteralivesum == 0)//怪物已死
	{
		this->stopAllActions();
		this->unscheduleAllSelectors();
		//进入第三幕 前进
		show_goahead();
		return;
	}
	//选择怪物
	int pos = monster_alive[rand() % monsteralivesum];     
	//选择英雄
	int dst = hero_alive[rand() % hero_alive.size()];
	switch (pos)
	{
	case 0:
		monster_0_skill(pos,dst);
		break;
	case 1:
		monster_1_skill(pos,dst);
		break;
	case 2:
		monster_2_skill(pos,dst);
		break;
	case 3:
		monster_3_skill(pos,dst);
		break;
	case 4:
		monster_4_skill(pos,dst);
		break;
	case 5:
		monster_5_skill(pos,dst);
		break;
	}
	this->scheduleOnce(schedule_selector(BattleLayer::second_hero_play),1.7f);
}
//第三幕英雄打
void BattleLayer::third_hero_play(float)
{
	gongjifang = true;
	//判断英雄是否死了
	int heroalivesum = hero_alive.size();
	if(heroalivesum == 0)//英雄已死
	{
		this->stopAllActions();
		this->unscheduleAllSelectors();
		//弹出战斗失败
		showFail();
		return;
	}
	//选择英雄
	int pos = hero_alive[rand() % heroalivesum];
	//选择怪物
	int dst = monster_alive[rand() % monster_alive.size()];
	switch (pos)
	{
	case 0:
		hero_0_skill(pos,dst);
		break;
	case 1:
		hero_1_skill(pos,dst);
		break;
	case 2:
		hero_2_skill(pos,dst);
		break;
	case 3:
		hero_3_skill(pos,dst);
		break;
	case 4:
		hero_4_skill(pos,dst);
		break;
	}
	this->scheduleOnce(schedule_selector(BattleLayer::third_monster_play),1.7f);
}
//第三幕怪物打
void BattleLayer::third_monster_play(float)
{
	gongjifang = false;
	//判断怪物是否死了
	int monsteralivesum = monster_alive.size();
	if(monsteralivesum == 0)//怪物已死
	{
		this->stopAllActions();
		this->unscheduleAllSelectors();
		//弹出战斗胜利
		showVictory();
		return;
	}
	//选择怪物
	int pos = monster_alive[rand() % monsteralivesum];     
	//选择英雄
	int dst = hero_alive[rand() % hero_alive.size()];
	switch (pos)
	{
	case 6:
		monster_6_skill(pos,dst);
		break;
	case 7:
		monster_7_skill(pos,dst);
		break;
	case 8:
		monster_8_skill(pos,dst);
		break;
	case 9:
		monster_9_skill(pos,dst);
		break;
	case 10:
		monster_10_skill(pos,dst);
		break;
	}
	this->scheduleOnce(schedule_selector(BattleLayer::third_hero_play),1.7f);
}
//英雄技能
void BattleLayer::hero_0_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill02.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill08.mp3");
	show_skill_normal(pos,hero,pos_hero_x,pos_hero_y,1,dst,pos_monster_x,pos_monster_y);//发技能
	show_hit_skill(pos,"blizzard_skill","blizzard_0001.png",dst,pos_monster_x,pos_monster_y);//敌人攻击后的反应
	show_hit_value(pos,hero_attack,dst,pos_monster_x,pos_monster_y);//显示伤害值
}

void BattleLayer::hero_1_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill01.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill07.mp3");
	show_skill_normal(pos,hero,pos_hero_x,pos_hero_y,0,dst,pos_monster_x,pos_monster_y);//发技能
	show_hit_skill(pos,"tenarmy_skill","tenarmy_01.png",dst,pos_monster_x,pos_monster_y);//敌人攻击后的反应
	show_hit_value(pos,hero_attack,dst,pos_monster_x,pos_monster_y);//显示伤害值
}

void BattleLayer::hero_2_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill06.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill09.mp3");
	show_skill(pos,hero,pos_hero_x,pos_hero_y,"customattack_skill","attack0002.png",dst);
	show_hit_skill(pos,"zhongji_skill","zhongji_shan0001.png",dst,pos_monster_x,pos_monster_y);//敌人攻击后的反应
	show_hit_value(pos,hero_attack,dst,pos_monster_x,pos_monster_y);//显示伤害值
}

void BattleLayer::hero_3_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill03.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill10.mp3");
	show_skill(pos,hero,pos_hero_x,pos_hero_y,"heal_skill","heal_1.png",dst);
	show_hit_skill(pos,"thunder_skill","thunder_dian.png",dst,pos_monster_x,pos_monster_y);//敌人攻击后的反应
	show_hit_value(pos,hero_attack,dst,pos_monster_x,pos_monster_y);//显示伤害值
}

void BattleLayer::hero_4_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill02.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill04.mp3");
	show_skill_normal(pos,hero,pos_hero_x,pos_hero_y,1,dst,pos_monster_x,pos_monster_y);//发技能
	show_hit_skill(pos,"rock_skill","thunder_shandian.png",dst,pos_monster_x,pos_monster_y);//敌人攻击后的反应
	show_hit_value(pos,hero_attack,dst,pos_monster_x,pos_monster_y);//显示伤害值
}
//怪物技能(小怪)
void BattleLayer::monster_0_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill02.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill05.mp3");
	show_skill_normal(pos,monster,pos_monster_x,pos_monster_y,1,dst,pos_hero_x,pos_hero_y);
	show_hit_skill(pos,"windhit_skill","windhit_01.png",dst,pos_hero_x,pos_hero_y);
	show_hit_value(pos,monster_attack,dst,pos_hero_x,pos_hero_y);
}
void BattleLayer::monster_1_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill01.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill08.mp3");
	show_skill_normal(pos,monster,pos_monster_x,pos_monster_y,0,dst,pos_hero_x,pos_hero_y);
	show_hit_skill(pos,"blizzard_skill","blizzard_0001.png",dst,pos_hero_x,pos_hero_y);
	show_hit_value(pos,monster_attack,dst,pos_hero_x,pos_hero_y);
}
void BattleLayer::monster_2_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill02.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill05.mp3");
	show_skill_normal(pos,monster,pos_monster_x,pos_monster_y,1,dst,pos_hero_x,pos_hero_y);
	show_hit_skill(pos,"windhit_skill","windhit_01.png",dst,pos_hero_x,pos_hero_y);
	show_hit_value(pos,monster_attack,dst,pos_hero_x,pos_hero_y);
}
void BattleLayer::monster_3_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill01.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill08.mp3");
	show_skill_normal(pos,monster,pos_monster_x,pos_monster_y,0,dst,pos_hero_x,pos_hero_y);
	show_hit_skill(pos,"blizzard_skill","blizzard_0001.png",dst,pos_hero_x,pos_hero_y);
	show_hit_value(pos,monster_attack,dst,pos_hero_x,pos_hero_y);
}
void BattleLayer::monster_4_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill02.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill05.mp3");
	show_skill_normal(pos,monster,pos_monster_x,pos_monster_y,1,dst,pos_hero_x,pos_hero_y);
	show_hit_skill(pos,"windhit_skill","windhit_01.png",dst,pos_hero_x,pos_hero_y);
	show_hit_value(pos,monster_attack,dst,pos_hero_x,pos_hero_y);
}
void BattleLayer::monster_5_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill01.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill08.mp3");
	show_skill_normal(pos,monster,pos_monster_x,pos_monster_y,0,dst,pos_hero_x,pos_hero_y);
	show_hit_skill(pos,"blizzard_skill","blizzard_0001.png",dst,pos_hero_x,pos_hero_y);
	show_hit_value(pos,monster_attack,dst,pos_hero_x,pos_hero_y);
}
//怪物技能(大怪)
void BattleLayer::monster_6_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill08.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill10.mp3");
	show_skill(pos,monster,pos_monster_x,pos_monster_y,"heal_skill","heal_1.png",dst);
	show_hit_skill(pos,"blizzard_skill","blizzard_0001.png",dst,pos_hero_x,pos_hero_y);
	show_hit_value(pos,monster_attack,dst,pos_hero_x,pos_hero_y);
}

void BattleLayer::monster_7_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill06.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill09.mp3");
	show_skill(pos,monster,pos_monster_x,pos_monster_y,"customattack_skill","attack0002.png",dst);
	show_hit_skill(pos,"zhongji_skill","zhongji_shan0001.png",dst,pos_hero_x,pos_hero_y);
	show_hit_value(pos,monster_attack,dst,pos_hero_x,pos_hero_y);
}

void BattleLayer::monster_8_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill01.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill03.mp3");
	show_skill_normal(pos,monster,pos_monster_x,pos_monster_y,0,dst,pos_hero_x,pos_hero_y);
	show_hit_skill(pos,"thunder_skill","thunder_dian.png",dst,pos_hero_x,pos_hero_y);
	show_hit_value(pos,monster_attack,dst,pos_hero_x,pos_hero_y);
}

void BattleLayer::monster_9_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill02.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill05.mp3");
	show_skill_normal(pos,monster,pos_monster_x,pos_monster_y,1,dst,pos_hero_x,pos_hero_y);
	show_hit_skill(pos,"windhit_skill","windhit_01.png",dst,pos_hero_x,pos_hero_y);
	show_hit_value(pos,monster_attack,dst,pos_hero_x,pos_hero_y);
}

void BattleLayer::monster_10_skill(int pos,int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill07.mp3");
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_skill10.mp3");
	show_skill(pos,monster,pos_monster_x,pos_monster_y,"heal_skill","heal_1.png",dst);
	show_hit_skill(pos,"tenarmy_skill","tenarmy_01.png",dst,pos_hero_x,pos_hero_y);
	show_hit_value(pos,monster_attack,dst,pos_hero_x,pos_hero_y);
}

//英雄向前走
void BattleLayer::runCard()
{
	for(int i = 0; i < hero_alive.size(); ++i)
	{
		CCSequence* seq = CCSequence::create(
			             CCMoveTo::create(0.1f,ccp(hero[hero_alive[i]]->getPositionX(),hero[hero_alive[i]]->getPositionY()+10)),
						 CCMoveTo::create(0.1f,ccp(hero[hero_alive[i]]->getPositionX(),hero[hero_alive[i]]->getPositionY())),
						 CCMoveTo::create(0.1f,ccp(hero[hero_alive[i]]->getPositionX(),hero[hero_alive[i]]->getPositionY()-10)),
						 CCMoveTo::create(0.1f,ccp(hero[hero_alive[i]]->getPositionX(),hero[hero_alive[i]]->getPositionY())),NULL);
		hero[hero_alive[i]]->runAction(CCRepeat::create(seq,3));
	}
}
//英雄摇晃
void BattleLayer::runcardshake()
{
	for(int i = 0; i < hero_alive.size(); ++i)
	{
		CCSequence* seq = CCSequence::create(CCRotateTo::create(0.1f,-1),CCRotateTo::create(0.2f,1),CCRotateTo::create(0.1f,0),NULL);
		hero[hero_alive[i]]->runAction(CCRepeat::create(seq,3));
	}
}
//背景向后走
void BattleLayer::runBK()
{
	effectId = SimpleAudioEngine::sharedEngine()->playEffect("mp3/battle_run.mp3",true);
	CCMoveBy* by1 = CCMoveBy::create(0.1f,ccp(0,-45));
	bk_1->runAction(CCSequence::create(CCRepeat::create(by1,11),CCCallFunc::create(this,callfunc_selector(BattleLayer::adjustBK1)),NULL));
	CCMoveBy* by2 = CCMoveBy::create(0.1f,ccp(0,-45));
	bk_2->runAction(CCSequence::create(CCRepeat::create(by2,11),CCCallFunc::create(this,callfunc_selector(BattleLayer::adjustBK2)),NULL));
}

void BattleLayer::adjustBK1()
{
	SimpleAudioEngine::sharedEngine()->stopEffect(effectId);
	if(bkmovecount == 1)bk_1->setPosition(ccp(visibleSize.width/2,0));
	else  bk_1->setPosition(ccp(visibleSize.width/2,-visibleSize.height/2));
}

void BattleLayer::adjustBK2()
{
	if(bkmovecount == 1)bk_2->setPosition(ccp(visibleSize.width/2,visibleSize.height));
	else  bk_2->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
}

//发动画技能
void BattleLayer::show_skill(int pos,CCNode** node,int* x,int* y,const char* skillname,const char * skill_spritename,int dst)
{
	node[pos]->runAction(CCSequence::create(CCRotateTo::create(0.1f,5),CCRotateTo::create(0.1f,-5),CCRotateTo::create(0.1f,0),NULL));
	CCAnimate* skill_animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(skillname));
	CCSprite* skill_sprite = CCSprite::createWithSpriteFrameName(skill_spritename);
	skill_sprite->setPosition(ccp(x[pos],y[pos]));
	this->addChild(skill_sprite);
	skill_sprite->runAction(CCSequence::create(skill_animate,CCCallFuncN::create(this,callfuncN_selector(BattleLayer::remove_skill)),NULL));
}

//发普通技能
void BattleLayer::show_skill_normal(int pos,CCNode** node,int* x,int* y,int type,int dst,int* dx,int* dy)
{
	if(type == 0)
	{
		node[pos]->runAction(CCSequence::create(CCRotateTo::create(0.1f,5),CCRotateTo::create(0.1f,-5),CCRotateTo::create(0.1f,0),NULL));
		CCSprite* sword_left = CCSprite::create("ui/hit0003.png");
		CCSprite* sword_right = CCSprite::create("ui/hit0003.png");
		sword_left->setFlipX(true);
		CCNode* sword = CCNode::create();
		sword->addChild(sword_left);
		sword->addChild(sword_right);
		sword->setPosition(ccp(x[pos],y[pos]));
		this->addChild(sword);
		sword->runAction(CCSequence::create(CCFadeIn::create(0.2f),
											CCScaleTo::create(0.1f,1.1f),
											CCScaleTo::create(0.1f,0.9f),
											CCScaleTo::create(0.1f,1.0f),
											CCCallFuncN::create(this,callfuncN_selector(BattleLayer::remove_skill)),NULL));
	}
	else if(type == 1)
	{
		node[pos]->runAction(CCSequence::create(CCRotateTo::create(0.1f,5),CCRotateTo::create(0.1f,-5),CCRotateTo::create(0.1f,0),NULL));
		CCSprite* iceball = CCSprite::create("ui/shoot.png");
		iceball->setPosition(ccp(x[pos],y[pos]));
		this->addChild(iceball);
		iceball->runAction(CCSequence::create(CCFadeIn::create(0.1f),
											CCMoveTo::create(0.2f,ccp(dx[dst],dy[dst])),
											CCScaleTo::create(0.05f,1.1f),
											CCScaleTo::create(0.05f,0.8f),
											CCScaleTo::create(0.05f,1.0f),
											CCCallFuncN::create(this,callfuncN_selector(BattleLayer::remove_skill)),NULL));
	}
}
//移除执行动画的过程中加载的精灵
void BattleLayer::remove_skill(CCNode* pSender)
{
	this->removeChild(pSender);
}
//被攻击方受攻击后的反应
void BattleLayer::show_hit_skill(int pos,const char* skillname,const char * skill_spritename,int dst,int* dx,int* dy)
{
	CCAnimate* skill_animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(skillname));
	CCSprite* skill_sprite = CCSprite::createWithSpriteFrameName(skill_spritename);
	skill_sprite->setPosition(ccp(dx[dst],dy[dst]));
	this->addChild(skill_sprite);
	int *p = new int[2];
	p[0] = pos;
	p[1] = dst;
	skill_sprite->runAction(CCSequence::create(skill_animate,CCCallFuncND::create(this,callfuncND_selector(BattleLayer::remove_hit_skill),p),NULL));
}
//移除动画 并做攻击结算
void BattleLayer::remove_hit_skill(CCNode* pSender,void* p)
{
	this->removeChild(pSender);
	//本次攻击的结算
	int* pp = (int*)p;
	int pos = pp[0];//攻击方
	int dst = pp[1];//被攻击方
	delete pp;
	if(gongjifang)//英雄打
	{
		monster_life[monster_order[dst]] -= hero_attack[pos];
		if(monster_life[monster_order[dst]] <= 0)
		{
			//去掉已死的
			for (vector<int>::iterator it = monster_alive.begin(); it !=  monster_alive.end();)
			{
				if(*it == dst)
				{
					it = monster_alive.erase(it);
					break;
				}
				else
				{
					++it;
				}
			}
			monster_die(dst);
		}
	}
	else
	{
		hero_life[dst] -= monster_attack[monster_order[pos]];
		if(hero_life[dst] <= 0)
		{
			////去掉已死的
			for (vector<int>::iterator it = hero_alive.begin(); it !=  hero_alive.end();)
			{
				if(*it == dst)
				{
					it = hero_alive.erase(it);
					break;
				}
				else
				{
					++it;
				}
			}
			hero[dst]->setVisible(false);
			SimpleAudioEngine::sharedEngine()->playEffect("mp3/battle_herodead.mp3");
		}
	}
}
//显示伤害值
void BattleLayer::show_hit_value(int pos,int* posattack,int dst,int* dx,int* dy)
{
	CCString* str = CCString::createWithFormat("%d",posattack[pos]);
	CCLabelBMFont* sprite_value = CCLabelBMFont::create(str->m_sString.c_str(),"fonts/number_red.fnt",45);
	sprite_value->setPosition(ccp(dx[dst],dy[dst]));
	sprite_value->setOpacity(0);
	this->addChild(sprite_value);
	sprite_value->runAction(CCSequence::create(CCFadeIn::create(0.5f),
		CCScaleTo::create(0.2f,1.3f),
		CCMoveBy::create(0.2f,ccp(0,10)),
		CCFadeOut::create(0.5f),
		CCCallFuncN::create(this,callfuncN_selector(BattleLayer::remove_hit_value)),NULL));
}
//移除伤害值
void BattleLayer::remove_hit_value(CCNode* pSender)
{
	this->removeChild(pSender);
}

//怪物死亡
void BattleLayer::monster_die(int dst)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/battle_monsterdead.mp3");
	CCRepeat* monster_shock = CCRepeat::create(CCSequence::create(CCRotateTo::create(0.1f,-10),CCRotateTo::create(0.1f,10),CCRotateTo::create(0.1f,0),NULL),2);
	int* p = new int(dst);
	monster[dst]->runAction(CCSequence::create(monster_shock,CCCallFuncND::create(this,callfuncND_selector(BattleLayer::show_ghost),p),NULL));
}
//显示怪物的灵魂
void BattleLayer::show_ghost(CCNode* ,void* p)
{
	int dst = *(int*)p;
	delete (int*)p;
	monster[dst]->setVisible(false);//将怪物隐藏
	CCSprite* ghost = CCSprite::create("ui/ghost.png");
	ghost->setPosition(ccp(pos_monster_x[dst],pos_monster_y[dst]));
	this->addChild(ghost);
	ghost->runAction(CCSpawn::create(CCMoveBy::create(0.3f,ccp(0,30)),CCScaleTo::create(0.3f,0.9f),NULL));
	ghost->runAction(CCSequence::create(CCDelayTime::create(0.3f),CCFadeOut::create(0.3f),
		                              CCCallFuncN::create(this,callfuncN_selector(BattleLayer::remove_ghost)),NULL));
}

void BattleLayer::remove_ghost(CCNode* pSender)
{
	this->removeChild(pSender);
}
//显示前进标志
void BattleLayer::show_goahead()
{
	m_isShowGoAhead = true;
	goahead->setOpacity(0);
	goahead->setVisible(true);
	goahead->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0.7f),CCFadeOut::create(0.7f),NULL)));
}
//显示怪物
void BattleLayer::show_allmonster(float)
{
	if(m_curPlay == SECOND)
	{
		for(int i = 0; i < 6; ++i)monster[i]->setVisible(true);
	}
	else if(m_curPlay == THIRD)
	{
		for(int i = 6; i < 11; ++i)monster[i]->setVisible(true);
	}
}
//显示战斗胜利
void BattleLayer::showVictory()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/battle_win.mp3");
	CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0f);//恢复到原来的速度
	CCUserDefault::sharedUserDefault()->setBoolForKey("BattleResult",true);
	result = CCNode::create();
	result->setPosition(ccp(320,700));
	this->addChild(result);
	//闪光
	CCSprite* victory_flash = CCSprite::create("ui/victory_flash.png");
	result->addChild(victory_flash);
	victory_flash->runAction(CCRepeatForever::create(CCRotateBy::create(0.5f,90)));
	//两把斧子
	CCSprite* victory_weapon1 = CCSprite::createWithSpriteFrameName("victory_weapon1.png");
	result->addChild(victory_weapon1);
	victory_weapon1->setPosition(ccp(-50,100));
	CCSprite* victory_weapon2 = CCSprite::createWithSpriteFrameName("victory_weapon2.png");
	result->addChild(victory_weapon2);
	victory_weapon2->setPosition(ccp(50,100));
	//鼓
	CCSprite* victory_drum = CCSprite::createWithSpriteFrameName("victory_drum.png");
	result->addChild(victory_drum);
	victory_drum->setOpacity(0);
	victory_drum->setScale(0.2f);
	victory_drum->runAction(CCSpawn::create(CCScaleTo::create(0.2f,1.0f),CCFadeIn::create(0.2f),NULL));
	//战斗胜利
	CCSprite* victory_word = CCSprite::createWithSpriteFrameName("victory_word.png");
	result->addChild(victory_word);
	victory_word->setOpacity(0);
	victory_word->setScale(0.2f);
	victory_word->runAction(CCSpawn::create(CCScaleTo::create(0.2f,1.0f),CCFadeIn::create(0.2f),NULL));
	if(curGuanQia == Hero::sharedHero()->getCurChallengeGQ())//在竞技场
	{
		//更新关卡状态
		GuanQiaState::sharedGuanQiaState()->isComplete_GuanQia[curGuanQia] = true;
		Hero::sharedHero()->setCurChallengeGQ(Hero::sharedHero()->getCurChallengeGQ() + 1);
		//返回到战斗界面
		CCNotificationCenter::sharedNotificationCenter()->postNotification("ReturnArena");
		//去更新副本界面
		CCNotificationCenter::sharedNotificationCenter()->postNotification("ReturnLineup");
		CCNotificationCenter::sharedNotificationCenter()->postNotification("ReturnInstance");
	}
	else
	{
		//返回到副本界面
		CCNotificationCenter::sharedNotificationCenter()->postNotification("ReturnInstance");
	}
	this->scheduleOnce(schedule_selector(BattleLayer::showReult),4.0f);
}
//战斗失败
void BattleLayer::showFail()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/battle_failed.mp3");
	CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0f);//恢复到原来的速度
	CCUserDefault::sharedUserDefault()->setBoolForKey("BattleResult",false);
	result = CCNode::create();
	result->setPosition(ccp(320,700));
	this->addChild(result);
	//闪光
	CCSprite* fail_flash = CCSprite::create("ui/victory_flash.png");
	result->addChild(fail_flash);
	fail_flash->runAction(CCRepeatForever::create(CCRotateBy::create(0.5f,90)));
	//两把斧子
	CCSprite* failed_weapon1 = CCSprite::createWithSpriteFrameName("failed_weapon1.png");
	result->addChild(failed_weapon1);
	failed_weapon1->setPosition(ccp(-50,100));
	CCSprite* failed_weapon2 = CCSprite::createWithSpriteFrameName("failed_weapon2.png");
	result->addChild(failed_weapon2);
	failed_weapon2->setPosition(ccp(50,100));
	//鼓
	CCSprite* failed_gong = CCSprite::createWithSpriteFrameName("failed_gong.png");
	result->addChild(failed_gong);
	failed_gong->setOpacity(0);
	failed_gong->setScale(0.2f);
	failed_gong->runAction(CCSpawn::create(CCScaleTo::create(0.2f,1.0f),CCFadeIn::create(0.2f),NULL));
	//战斗失败
	CCSprite* failed_word = CCSprite::createWithSpriteFrameName("failed_word.png");
	result->addChild(failed_word);
	failed_word->setOpacity(0);
	failed_word->setScale(0.2f);
	failed_word->runAction(CCSpawn::create(CCScaleTo::create(0.2f,1.0f),CCFadeIn::create(0.2f),NULL));
	if(curGuanQia == Hero::sharedHero()->getCurChallengeGQ())//在竞技场
	{
		//返回到战斗界面
		CCNotificationCenter::sharedNotificationCenter()->postNotification("ReturnArena");
	}
	else
	{
		//返回到副本界面
		CCNotificationCenter::sharedNotificationCenter()->postNotification("ReturnInstance");
	}
	this->scheduleOnce(schedule_selector(BattleLayer::showReult),4.0f);
}

//显示结果
void BattleLayer::showReult(float)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/main.mp3",true);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("showBatleResult");
	CCDirector::sharedDirector()->popScene();
}

void BattleLayer::showText(float)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/battle_battlestart.mp3");
	if(m_curPlay == FIRST)
	{
		CCSprite* fight1 = CCSprite::createWithSpriteFrameName("fightstar_word_fight1.png");
		fight1->setPosition(ccp(visibleSize.width/2-50,visibleSize.height/2+5));
		fight1->setOpacity(0);
		CCSprite* fight2 = CCSprite::createWithSpriteFrameName("fightstar_word_fight2.png");
		fight2->setPosition(ccp(visibleSize.width/2+50,visibleSize.height/2+5));
		fight2->setOpacity(0);
		this->addChild(fight1);
		this->addChild(fight2);
		fight1->runAction(CCSequence::create(CCFadeIn::create(1.0f),CCFadeOut::create(1.0f),NULL));
		fight2->runAction(CCSequence::create(CCFadeIn::create(1.0f),CCFadeOut::create(1.0f),NULL));
	}
	else if(m_curPlay == THIRD)
	{
		CCSprite* boss_text = CCSprite::createWithSpriteFrameName("fightstar_word_boss.png");
		boss_text->setPosition(ccp(350,480));
		this->addChild(boss_text);
		boss_text->setOpacity(0);
		boss_text->runAction(CCSpawn::create(CCMoveBy::create(0.5f,ccp(-60,0)),
			         CCSequence::create(CCFadeIn::create(0.25f),CCFadeOut::create(0.25f),NULL),NULL));
	}
}

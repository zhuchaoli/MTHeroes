#include "CardLevelupLayer.h"
#include "AppStringFile.h"
#include "AppMacros.h"
#include "ValueConvert.h"
#include "CardTeam.h"
#include "Hero.h"

bool CardLevelupLayer::init()
{
	if(!CCLayer::init())return false;
	initframe();
	initcontent();
	return true;
}

void CardLevelupLayer::initframe()
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
	//升级的背景
	CCSprite* listbase = CCSprite::create("ui/eatcardbase.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(ccp(visibleSize.width/2,410));
	this->addChild(listbase);
	//顶部文字背景
	CCSprite* middletitlebase = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("middletitlebase.png"));
	middletitlebase->setPosition(ccp(visibleSize.width/2,700));
	this->addChild(middletitlebase);
	//顶部文字
	CCSprite* titlenamemycardlevelup = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("titlename_eatcard.png"));
	titlenamemycardlevelup->setPosition(ccp(visibleSize.width/2,690));
	this->addChild(titlenamemycardlevelup);
	//返回按钮
	CCSprite* button_left_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_0.png"));
	CCSprite* button_left_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_1.png"));
	CCSprite* button_left_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_2.png"));
	CCMenuItemSprite* button_left_item = CCMenuItemSprite::create(button_left_nor,
																	button_left_sel,
																	button_left_disable,
																	this,
																	menu_selector(CardLevelupLayer::menu_return_callback));
	CCSprite* text_return = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_return.png"));
	text_return->setPosition(ccp(button_left_nor->getContentSize().width/2-15,button_left_nor->getContentSize().height/2));
	button_left_item->addChild(text_return);
	CCMenu* button_left_menu = CCMenu::create(button_left_item,NULL);
	button_left_menu->setPosition(ccp(button_left_nor->getContentSize().width/2-10,687));
	this->addChild(button_left_menu);
	//卡牌升级框
	CCSprite* card_levelup_base = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bigcard_empty.png"));
	card_levelup_base->setPosition(ccp(visibleSize.width/2,530));
	this->addChild(card_levelup_base);
	//卡牌升级属性背景
	CCSprite* card_levelup_pro_base = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("cardinfobase.png"));
	card_levelup_pro_base->setPosition(ccp(visibleSize.width/2,350));
	this->addChild(card_levelup_pro_base);
	//左三排背景
	CCSprite* left_eated_01_bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_empty.png"));
	CCSprite* left_eated_02_bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_empty.png"));
	CCSprite* left_eated_03_bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_empty.png"));
	left_eated_01_bk->setPosition(ccp(120,580));
	left_eated_02_bk->setPosition(ccp(120,480));
	left_eated_03_bk->setPosition(ccp(120,380));
	this->addChild(left_eated_01_bk);
	this->addChild(left_eated_02_bk);
	this->addChild(left_eated_03_bk);
	//右三排背景
	CCSprite* right_eated_01_bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_empty.png"));
	CCSprite* right_eated_02_bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_empty.png"));
	CCSprite* right_eated_03_bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_empty.png"));
	right_eated_01_bk->setPosition(ccp(520,580));
	right_eated_02_bk->setPosition(ccp(520,480));
	right_eated_03_bk->setPosition(ccp(520,380));
	this->addChild(right_eated_01_bk);
	this->addChild(right_eated_02_bk);
	this->addChild(right_eated_03_bk);
	//花费值背景
	CCSprite* need_eat_pro_base = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eatcard_base2.png"));
	need_eat_pro_base->setScale(2.0f);
	need_eat_pro_base->setPosition(ccp(visibleSize.width/2,245));
	this->addChild(need_eat_pro_base);
	//选择吞噬英雄按钮
	CCSprite* choosefood_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* choosefood_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* choosefood_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	choose_food_item = CCMenuItemSprite::create(choosefood_nor,
												choosefood_sel,
												choosefood_disable,
												this,
												menu_selector(CardLevelupLayer::menu_choose_food));
	choose_food_item->setScale(0.8f);
	CCSprite* text_choosefood = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_food.png"));
	text_choosefood->setPosition(ccp(choosefood_nor->getContentSize().width/2,choosefood_nor->getContentSize().height/2));
	choose_food_item->addChild(text_choosefood);
	CCMenu* choosefood_menu = CCMenu::create(choose_food_item,NULL);
	choosefood_menu->setPosition(ccp(visibleSize.width/2-150,183));
	this->addChild(choosefood_menu);
	//开始升级按钮
	CCSprite* levelup_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* levelup_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* levelup_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	startlevelup_item = CCMenuItemSprite::create(levelup_nor,
												levelup_sel,
												levelup_disable,
												this,
												menu_selector(CardLevelupLayer::menu_cardlevelupUI_startlevelup));
	startlevelup_item->setScale(0.8f);
	CCSprite* text_levelup = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_stareat.png"));
	text_levelup->setPosition(ccp(levelup_nor->getContentSize().width/2,levelup_nor->getContentSize().height/2));
	startlevelup_item->addChild(text_levelup);
	CCMenu* levelup_menu = CCMenu::create(startlevelup_item,NULL);
	levelup_menu->setPosition(ccp(visibleSize.width/2+150,183));
	this->addChild(levelup_menu);
	startlevelup_item->setEnabled(false);
}

void CardLevelupLayer::initcontent()
{
	int x[] = {145,145,145,545,545,545};
	int y[] = {605,505,405,605,505,405};
	//卡牌
	card = CCNode::create();
	card->setPosition(ccp(320,530));
	this->addChild(card);
	CCSprite* card_frame= CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bigcard_empty.png"));
	card->addChild(card_frame);
	//要升级的卡牌 (需要选择)
	int index = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectedcardindex");
	string content_key = ValueConvert::getSelectCardKey(index);
	CCSprite* card_content = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(AppStringFile::sharedAppStringFile()->getStringForKey(content_key)));
	card->addChild(card_content);
	//卡牌右下角的图标
	CCSprite* card_occupation_elite = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_occupation_base_elite.png"));
	card_occupation_elite->setScale(0.8f);
	card_occupation_elite->setPosition(ccp(15,-20));
	card->addChild(card_occupation_elite);
	CCSprite* occupaction_warrior = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_occupation_warrior_button.png"));
	occupaction_warrior->setScale(1.6f);
	occupaction_warrior->setPosition(ccp(65,-78));
	card->addChild(occupaction_warrior);
	//加号
	for(int i = 0; i < 6; ++i)
	{
		add[i] = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("add.png"));
		add[i]->setPosition(ccp(x[i],y[i]));
		this->addChild(add[i]);
		add[i]->runAction(CCRepeatForever::create(CCBlink::create(3.0f,5)));
	}
	
	//当前生命属性
	string strtext = AppStringFile::sharedAppStringFile()->getStringForKey("levelup_life_text");
	CCLabelTTF* life_text = CCLabelTTF::create(strtext.c_str(),"Arial",18);
	life_text->setPosition(ccp(280,400));
	this->addChild(life_text);
	//生命值
	CCString* str = CCString::create("");
	str->initWithFormat("%d",CardTeam::sharedCardTeam()->getLifeByKey(index));
	lifevalue = CCLabelTTF::create(str->m_sString.c_str(),"Arial",18);
	lifevalue->setPosition(ccp(350,400));
	this->addChild(lifevalue);
	//当前攻击属性
	strtext = AppStringFile::sharedAppStringFile()->getStringForKey("levelup_attack_text");
	CCLabelTTF* attack_text = CCLabelTTF::create(strtext.c_str(),"Arial",18);
	attack_text->setPosition(ccp(280,375));
	this->addChild(attack_text);
	//攻击值
	str->initWithFormat("%d",CardTeam::sharedCardTeam()->getAttackByKey(index));
	attackvalue = CCLabelTTF::create(str->m_sString.c_str(),"Arial",18);
	attackvalue->setPosition(ccp(350,375));
	this->addChild(attackvalue);
	//要增加的生命文本
	strtext = AppStringFile::sharedAppStringFile()->getStringForKey("levelup_addlife_text");
	CCLabelTTF* addlife_text = CCLabelTTF::create(strtext.c_str(),"Arial",18);
	addlife_text->setPosition(ccp(250,340));
	this->addChild(addlife_text);
	//要增加的攻击文本
	strtext = AppStringFile::sharedAppStringFile()->getStringForKey("levelup_addattack_text");
	CCLabelTTF* addattack_text = CCLabelTTF::create(strtext.c_str(),"Arial",18);
	addattack_text->setPosition(ccp(250,305));
	this->addChild(addattack_text);
	//要增加的生命进度条
	CCSprite* progress1_bk = CCSprite::create("ui/exp1_0.png");
	progress1_bk->setPosition(ccp(286,340));
	progress1_bk->setAnchorPoint(ccp(0,0.5));
	this->addChild(progress1_bk);
	//要增加的攻击进度条
	CCSprite* progress2_bk = CCSprite::create("ui/exp1_0.png");
	progress2_bk->setPosition(ccp(286,305));
	progress2_bk->setAnchorPoint(ccp(0,0.5));
	this->addChild(progress2_bk);

	//要消耗的金币
	strtext = AppStringFile::sharedAppStringFile()->getStringForKey("levelup_eatmoney_text");
	CCLabelTTF* eatmoney_text = CCLabelTTF::create(strtext.c_str(),"Consolas",25);
	eatmoney_text->setPosition(ccp(140,248));
	eatmoney_text->setColor(ccc3(255,255,0));
	this->addChild(eatmoney_text);
	eatmoneyvalue = CCLabelTTF::create("","Consolas",25);
	eatmoneyvalue->setPosition(ccp(230,248));
	this->addChild(eatmoneyvalue);
	//要消耗的符石
	strtext = AppStringFile::sharedAppStringFile()->getStringForKey("levelup_eatdiamon_text");
	CCLabelTTF* eatdiamon_text = CCLabelTTF::create(strtext.c_str(),"Consolas",25);
	eatdiamon_text->setPosition(ccp(405,248));
	eatdiamon_text->setColor(ccc3(255,255,0));
	this->addChild(eatdiamon_text);
    eatdiamonvalue = CCLabelTTF::create("","Consolas",25);
	eatdiamonvalue->setPosition(ccp(500,248));
	this->addChild(eatdiamonvalue);
}

void CardLevelupLayer::menu_return_callback(CCObject*)
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification("ReturnToMain");
}

void CardLevelupLayer::menu_cardlevelupUI_startlevelup(CCObject*)
{
	int x[] = {120,120,120,520,520,520};
	int y[] = {580,480,380,580,480,380};
	choose_food_item->setEnabled(true);
	startlevelup_item->setEnabled(false);
	//判断金币和符石是否足够
	if(Hero::sharedHero()->getMoney() < submoneysum || Hero::sharedHero()->getDiamond() < subdiamonsum)
	{
		//弹出模态对话框 告诉金币和符石不足
		DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("moneyanddiamonlack_tip"));
		this->addChild(layer);
		choose_food_item->setEnabled(false);
		startlevelup_item->setEnabled(false);
		return;
	}
	//减掉金币和符石
	Hero::sharedHero()->setMoney(Hero::sharedHero()->getMoney()-submoneysum);
	Hero::sharedHero()->setDiamond(Hero::sharedHero()->getDiamond()-subdiamonsum);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMoneyAndDiamon");
	//加上生命和攻击
	int index = CCUserDefault::sharedUserDefault()->getIntegerForKey("selectedcardindex");
	CardTeam::sharedCardTeam()->setLifeByKey(index,addlifesum);
	CardTeam::sharedCardTeam()->setAttackByKey(index,addattacksum);
	CCString* str = CCString::create("");
	str->initWithFormat("%d",CardTeam::sharedCardTeam()->getLifeByKey(index));
	lifevalue->setString(str->m_sString.c_str());
	str->initWithFormat("%d",CardTeam::sharedCardTeam()->getAttackByKey(index));
	attackvalue->setString(str->m_sString.c_str());
	//被吞噬的卡牌数量减一
	CardTeam* cardteam = CardTeam::sharedCardTeam();
	cardteam->seteatedcard0count(cardteam->geteatedcard0count()+isCardSelect[0]);
	cardteam->seteatedcard1count(cardteam->geteatedcard1count()+isCardSelect[1]);
	cardteam->seteatedcard2count(cardteam->geteatedcard2count()+isCardSelect[2]);
	cardteam->seteatedcard3count(cardteam->geteatedcard3count()+isCardSelect[3]);
	cardteam->seteatedcard4count(cardteam->geteatedcard4count()+isCardSelect[4]);
	cardteam->seteatedcard5count(cardteam->geteatedcard5count()+isCardSelect[5]);
	//更新团队实力
	Hero::sharedHero()->setTeamLv(Hero::sharedHero()->getTeamLv() + (addlifesum + addattacksum) / 2);
	//动画效果
	addlife_progress->setPercentage(0);
	addattack_progress->setPercentage(0);
	CCAnimation* littlecard_flash = CCAnimation::create();
	for(int i = 17; i > 1; --i)
	{
		str->initWithFormat("eatcard_100%02d.png",i);
		littlecard_flash->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str->m_sString.c_str()));
	}
	littlecard_flash->setDelayPerUnit(0.01f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(littlecard_flash,"littlecard_flash");
	CCSprite* littlecard_flash_sprite[6];
	for(int i = 0; i < 6; ++i)
	{
		littlecard_flash_sprite[i] = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("eatcard_10002.png"));
		littlecard_flash_sprite[i]->setPosition(ccp(x[i],y[i]));
		this->addChild(littlecard_flash_sprite[i]);
		CCAnimate* animate_flash = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("littlecard_flash"));
		CCMoveTo* moveto = CCMoveTo::create(0.5f,ccp(320,530));
		CCSpawn* spawn_flash = CCSpawn::create(animate_flash,moveto,NULL);
		CCCallFuncN * flash_down = CCCallFuncN::create(this,callfuncN_selector(CardLevelupLayer::littlecard_flash_done));
		CCSequence* seq = CCSequence::create(spawn_flash,flash_down,NULL);
		littlecard_flash_sprite[i]->runAction(seq);
	}
	this->scheduleUpdate();
}

void CardLevelupLayer::menu_choose_food(CCObject*)
{
	int x[] = {120,120,120,520,520,520};
	int y[] = {580,480,380,580,480,380};
	int index = 0;
	addlifesum = 0;
	addattacksum = 0;
	submoneysum = 0;
	subdiamonsum = 0;
	CCSprite* littlecard_content[6];
	for(int i = 0; i < 6; ++i)
	{
		isCardSelect[i] = 0;
		add[i]->setOpacity(0);
		littlecard_content[i] = NULL;
		littlecard[i] = CCNode::create();
		this->addChild(littlecard[i]);
		littlecard[i]->setScale(0.9f);
	}
	//先要判断是否有可用的英雄吞噬
	//卡牌1是否有
	if(CardTeam::sharedCardTeam()->geteatedcard0count() > 0)
	{
		isCardSelect[0] = -1;
		littlecard_content[0] = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard0"));
		littlecard[0]->setPosition(ccp(x[index],y[index]));
		littlecard[0]->addChild(littlecard_content[0]);
		addlifesum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard0_addlife"));
		addattacksum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard0_addattack"));
		submoneysum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard0_submoney"));
		subdiamonsum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard0_subdiamon"));
		index++;
	}
	//卡牌2是否有
	if(CardTeam::sharedCardTeam()->geteatedcard1count() > 0)
	{
		isCardSelect[1] = -1;
		littlecard_content[1] = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard1"));
		littlecard[1]->setPosition(ccp(x[index],y[index]));
		littlecard[1]->addChild(littlecard_content[1]);
		addlifesum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard1_addlife"));
		addattacksum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard1_addattack"));
		submoneysum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard1_submoney"));
		subdiamonsum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard1_subdiamon"));
		index++;
	}
	//卡牌3是否有
	if(CardTeam::sharedCardTeam()->geteatedcard2count() > 0)
	{
		isCardSelect[2] = -1;
		littlecard_content[2] = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard2"));
		littlecard[2]->setPosition(ccp(x[index],y[index]));
		littlecard[2]->addChild(littlecard_content[2]);
		addlifesum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard2_addlife"));
		addattacksum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard2_addattack"));
		submoneysum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard2_submoney"));
		subdiamonsum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard2_subdiamon"));
		index++;
	}
	//卡牌4是否有
	if(CardTeam::sharedCardTeam()->geteatedcard3count() > 0)
	{
		isCardSelect[3] = -1;
		littlecard_content[3] = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard3"));
		littlecard[3]->setPosition(ccp(x[index],y[index]));
		littlecard[3]->addChild(littlecard_content[3]);
		addlifesum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard3_addlife"));
		addattacksum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard3_addattack"));
		submoneysum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard3_submoney"));
		subdiamonsum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard3_subdiamon"));
		index++;
	}
	//卡牌5是否有
	if(CardTeam::sharedCardTeam()->geteatedcard4count() > 0)
	{
		isCardSelect[4] = -1;
		littlecard_content[4] = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard4"));
		littlecard[4]->setPosition(ccp(x[index],y[index]));
		littlecard[4]->addChild(littlecard_content[4]);
		addlifesum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard4_addlife"));
		addattacksum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard4_addattack"));
		submoneysum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard4_submoney"));
		subdiamonsum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard4_subdiamon"));
		index++;
	}
	//卡牌6是否有
	if(CardTeam::sharedCardTeam()->geteatedcard5count() > 0)
	{
		isCardSelect[5] = -1;
		littlecard_content[5] = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard5"));
		littlecard[5]->setPosition(ccp(x[index],y[index]));
		littlecard[5]->addChild(littlecard_content[5]);
		addlifesum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard5_addlife"));
		addattacksum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard5_addattack"));
		submoneysum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard5_submoney"));
		subdiamonsum += atoi(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcard5_subdiamon"));
		index++;
	}
	if(isCardSelect[0]+isCardSelect[1]+isCardSelect[2]+isCardSelect[3]+isCardSelect[4]+isCardSelect[5] == 0)
	{
		//没有吞噬卡牌 弹出模态对话框
		DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("eatedcardlack_tip"));
		this->addChild(layer);
		choose_food_item->setEnabled(false);
		return;
	}
	//生命的闪烁
	this->removeChild(addlife_progress);
	this->removeChild(addattack_progress);
	addlife_progress = CCProgressTimer::create(CCSprite::create("ui/exp1_2.png"));
	addlife_progress->setAnchorPoint(ccp(0,0.5f));
	addlife_progress->setPosition(ccp(286,340));
	addlife_progress->setBarChangeRate(ccp(1,0));//（1,0）表示横方向
	addlife_progress->setType(kCCProgressTimerTypeBar);//设置进度条为水平
	addlife_progress->setMidpoint(ccp(0,0));//设置进度条从左到右 从0开始
	addlife_progress->setPercentage(addlifesum/40);////////////
	this->addChild(addlife_progress);
	addlife_progress->runAction(CCBlink::create(2.0f,4));
	//攻击的闪烁
	addattack_progress = CCProgressTimer::create(CCSprite::create("ui/exp1_2.png"));
	addattack_progress->setAnchorPoint(ccp(0,0.5f));
	addattack_progress->setPosition(ccp(286,305));
	addattack_progress->setBarChangeRate(ccp(1,0));//（1,0）表示横方向
	addattack_progress->setType(kCCProgressTimerTypeBar);//设置进度条为水平
	addattack_progress->setMidpoint(ccp(0,0));//设置进度条从左到右 从0开始
	addattack_progress->setPercentage(addattacksum/40);//////////
	this->addChild(addattack_progress);
	addattack_progress->runAction(CCBlink::create(2.0f,4));
	//显示消耗的金币和符石
	CCString* str = CCString::create("");
	str->initWithFormat("%d",submoneysum);
	eatmoneyvalue->setString(str->m_sString.c_str());
	str->initWithFormat("%d",subdiamonsum);
	eatdiamonvalue->setString(str->m_sString.c_str());

	choose_food_item->setEnabled(false);
	startlevelup_item->setEnabled(true);
}

void CardLevelupLayer::littlecard_flash_done(CCNode* pSender)
{
	CCSprite* flash_sprite = (CCSprite*)pSender;
	this->removeChild(flash_sprite);
	for(int i = 0; i < 6; ++i)
	{
		if(littlecard[i])
		{
			this->removeChild(littlecard[i]);
			littlecard[i] = NULL;
		}
		add[i]->setOpacity(255);
	}
	CCScaleTo* scalebig = CCScaleTo::create(0.2f,1.1f);
	CCScaleTo* scalelittle = CCScaleTo::create(0.2f,0.9f);
	CCScaleTo* scalenor = CCScaleTo::create(0.2f,1.0f);
	CCSequence* seq = CCSequence::create(scalebig,scalelittle,scalenor,NULL);
	card->runAction(seq);
}

void CardLevelupLayer::update(float)
{
	int curlifeper = addlife_progress->getPercentage();
	int curattackper = addattack_progress->getPercentage();
	if(curlifeper < addlifesum/40 || curattackper < addattacksum/40)
	{
		if(curlifeper < addlifesum/40)addlife_progress->setPercentage(curlifeper+1);
		if(curattackper < addattacksum/40)addattack_progress->setPercentage(curattackper+1);
	}
	else
	{
		unscheduleUpdate();
	}
}


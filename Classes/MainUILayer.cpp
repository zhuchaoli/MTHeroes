#include "MainUILayer.h"
#include "AppStringFile.h"
#include "Hero.h"
#include "AppMacros.h"
#include "CardTeam.h"

bool MainUILayer::init()
{
	if(!CCLayer::init())return false;
	//����ͼƬ
	CCSprite* background1 = CCSprite::create("ui/background_1.jpg");
	background1->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	background1->setScale(2.23f);
	this->addChild(background1);
	configureTeamUI();
	configureMenuUI();
	m_curUI = MAIN_UI;
	//ע�����
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(MainUILayer::returncallback),"ReturnToMain",NULL);
	return true;
}

void MainUILayer::restoreToMainUI()
{
	switch(m_curUI)
	{
	case MAIL_UI:/*��������淵��*/
		this->removeChild(mailUI);
		configureTeamUI();
		configureMenuUI();
		break;
	case LEVELUP_UI:/*���������淵��*/
		this->removeChild(levelupUI);
		configureTeamUI();
		configureMenuUI();
		break;
	case CARD_UI:  /*��Ӣ�۽��淵��*/
		this->removeChild(cardUI);
		configureTeamUI();
		configureMenuUI();
		break;
	case TAST_UI:  /*�ӽ������淵��*/
		this->removeChild(tastUI);
		configureTeamUI();
		configureMenuUI();
		break;
	case MAIN_UI:
		break;
	default:
		break;
	}
	m_curUI = MAIN_UI;
}
//���յ�ReturnToMain���õĺ���
void MainUILayer::returncallback(CCObject*)
{
	restoreToMainUI();
}

//�����Ŷ�UI
void MainUILayer::configureTeamUI()
{
	//�Ŷӿ�
	team = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("team.png"));
	team->setPosition(ccp(visibleSize.width/2,visibleSize.height-320));
	this->addChild(team);
	CCSprite * text_myteam = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("titlename_team.png"));
	text_myteam->setPosition(ccp(text_myteam->getContentSize().width/2-40,team->getContentSize().height-33));
	team->addChild(text_myteam);
	//�쵼��(�Ŷ�����)
	CCSprite * text_leadership = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("leadship.png"));
	text_leadership->setPosition(ccp(text_leadership->getContentSize().width/2+5,35));
	team->addChild(text_leadership);
	CCLabelTTF* leadership = CCLabelTTF::create("5","Arial",32);
	leadership->setAnchorPoint(ccp(0,0.5));
	leadership->setPosition(ccp(180,35));
	team->addChild(leadership);
	//�Ŷ�ʵ��
	CCString* str = CCString::create("");
	CCSprite * text_teamlv = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("teamlv.png"));
	text_teamlv->setPosition(ccp(text_teamlv->getContentSize().width/2+290,35));
	team->addChild(text_teamlv);
	str->initWithFormat("%d",Hero::sharedHero()->getTeamLv());
	CCLabelTTF* teamlv = CCLabelTTF::create(str->m_sString.c_str(),"Arial",32);
	teamlv->setAnchorPoint(ccp(0,0.5));
	teamlv->setPosition(ccp(450,35));
	team->addChild(teamlv);
	//�ӳ���־
	CCSprite * sign_captain = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sign_captain.png"));
	sign_captain->setPosition(ccp(35,215));
	team->addChild(sign_captain);
	//�ӳ���ɫ
	CCSprite* captain_role = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey("captain_role"));////
	CCMenuItemSprite* item_role0 = CCMenuItemSprite::create(captain_role,captain_role,this,
		                                              menu_selector(MainUILayer::menu_selectcardcallback));
	CCSprite * captain_frame = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class1.png"));
	role_frame[0] = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class5_elite.png"));
	captain_frame->setPosition(ccp(captain_role->getContentSize().width/2,captain_role->getContentSize().height/2));
	role_frame[0]->setPosition(ccp(captain_role->getContentSize().width/2,captain_role->getContentSize().height/2));
	item_role0->addChild(captain_frame);
	item_role0->addChild(role_frame[0]);
	role_frame[0]->setTag(111);
	CCMenu* menu_role0 = CCMenu::create(item_role0,NULL);
	menu_role0->setPosition(ccp(97,160));
	team->addChild(menu_role0);
	//�ӳ���ʵ��(����+����)
	text_max[0] = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("arenamain_max.png"));
	text_max[0]->setPosition(ccp(97,91));
	team->addChild(text_max[0]);
	text_level[0] = CCNode::create();
	text_level[0]->setPosition(ccp(97,91));
	team->addChild(text_level[0]);
	str->initWithFormat("%d:%d",CardTeam::sharedCardTeam()->getcaption_life(),CardTeam::sharedCardTeam()->getcaption_attack());
	CCLabelTTF* text_lv_value_00 = CCLabelTTF::create(str->m_sString.c_str(),"Arial",17);
	text_lv_value_00->setColor(ccc3(59,199,255));
	text_lv_value_00->setPositionX(0);/////////
	text_level[0]->addChild(text_lv_value_00);
	text_level[0]->setVisible(false);
	//��Ա1
	CCSprite* teammate1_role = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey("teammate1_role"));////
	CCMenuItemSprite* item_role1 = CCMenuItemSprite::create(teammate1_role,teammate1_role,this,
															menu_selector(MainUILayer::menu_selectcardcallback));
	CCSprite * teammate1_frame = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class1.png"));
	role_frame[1] = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class5_elite.png"));
	teammate1_frame->setPosition(ccp(teammate1_role->getContentSize().width/2,teammate1_role->getContentSize().height/2));
	role_frame[1]->setPosition(ccp(teammate1_role->getContentSize().width/2,teammate1_role->getContentSize().height/2));
	item_role1->addChild(teammate1_frame);
	item_role1->addChild(role_frame[1]);
	role_frame[1]->setTag(111);
	CCMenu* menu_role1 = CCMenu::create(item_role1,NULL);
	menu_role1->setPosition(ccp(232,160));
	team->addChild(menu_role1);
	role_frame[1]->setVisible(false);
	//��Ա1��ʵ��
	text_max[1] = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("arenamain_max.png"));
	text_max[1]->setPosition(ccp(232,91));
	team->addChild(text_max[1]);
	text_level[1] = CCNode::create();
	text_level[1]->setPosition(ccp(232,91));
	team->addChild(text_level[1]);
	str->initWithFormat("%d:%d",CardTeam::sharedCardTeam()->getteammate1_life(),CardTeam::sharedCardTeam()->getteammate1_attack());
	CCLabelTTF* text_lv_value_01 = CCLabelTTF::create(str->m_sString.c_str(),"Arial",17);
	text_lv_value_01->setColor(ccc3(59,199,255));
	text_lv_value_01->setPositionX(0);
	text_level[1]->addChild(text_lv_value_01);
	text_level[1]->setVisible(false);
	//��Ա2
	CCSprite* teammate2_role = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey("teammate2_role"));////
	CCMenuItemSprite* item_role2 = CCMenuItemSprite::create(teammate2_role,teammate2_role,this,
														menu_selector(MainUILayer::menu_selectcardcallback));
	CCSprite * teammate2_frame = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class1.png"));
	role_frame[2] = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class5_elite.png"));
	teammate2_frame->setPosition(ccp(teammate2_role->getContentSize().width/2,teammate2_role->getContentSize().height/2));
	role_frame[2]->setPosition(ccp(teammate2_role->getContentSize().width/2,teammate2_role->getContentSize().height/2));
	item_role2->addChild(teammate2_frame);
	item_role2->addChild(role_frame[2]);
	role_frame[2]->setTag(111);
	CCMenu* menu_role2 = CCMenu::create(item_role2,NULL);
	menu_role2->setPosition(ccp(339,160));
	team->addChild(menu_role2);
	role_frame[2]->setVisible(false);
	//��Ա2��ʵ��
	text_max[2] = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("arenamain_max.png"));
	text_max[2]->setPosition(ccp(339,91));
	team->addChild(text_max[2]);
	text_level[2] = CCNode::create();
	text_level[2]->setPosition(ccp(339,91));
	team->addChild(text_level[2]);
	str->initWithFormat("%d:%d",CardTeam::sharedCardTeam()->getteammate2_life(),CardTeam::sharedCardTeam()->getteammate2_attack());
	CCLabelTTF* text_lv_value_02 = CCLabelTTF::create(str->m_sString.c_str(),"Arial",17);
	text_lv_value_02->setColor(ccc3(59,199,255));
	text_lv_value_02->setPositionX(0);
	text_level[2]->addChild(text_lv_value_02);
	text_level[2]->setVisible(false);
	//��Ա3
	CCSprite* teammate3_role = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey("teammate3_role"));////
	CCMenuItemSprite* item_role3 = CCMenuItemSprite::create(teammate3_role,teammate3_role,this,
															menu_selector(MainUILayer::menu_selectcardcallback));
	CCSprite * teammate3_frame = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class1.png"));
	role_frame[3] = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class5_elite.png"));
	teammate3_frame->setPosition(ccp(teammate3_role->getContentSize().width/2,teammate3_role->getContentSize().height/2));
	role_frame[3]->setPosition(ccp(teammate3_role->getContentSize().width/2,teammate3_role->getContentSize().height/2));
	item_role3->addChild(teammate3_frame);
	item_role3->addChild(role_frame[3]);
	role_frame[3]->setTag(111);
	CCMenu* menu_role3 = CCMenu::create(item_role3,NULL);
	menu_role3->setPosition(ccp(446,160));
	team->addChild(menu_role3);
	role_frame[3]->setVisible(false);
	//��Ա3��ʵ��
	text_max[3] = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("arenamain_max.png"));
	text_max[3]->setPosition(ccp(446,91));
	team->addChild(text_max[3]);
	text_level[3] = CCNode::create();
	text_level[3]->setPosition(ccp(446,91));
	team->addChild(text_level[3]);
	str->initWithFormat("%d:%d",CardTeam::sharedCardTeam()->getteammate3_life(),CardTeam::sharedCardTeam()->getteammate3_attack());
	CCLabelTTF* text_lv_value_03 = CCLabelTTF::create(str->m_sString.c_str(),"Arial",17);
	text_lv_value_03->setColor(ccc3(59,199,255));
	text_lv_value_03->setPositionX(0);
	text_level[3]->addChild(text_lv_value_03);
	text_level[3]->setVisible(false);
	//��Ա4
	CCSprite* teammate4_role = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey("teammate4_role"));////
	CCMenuItemSprite* item_role4 = CCMenuItemSprite::create(teammate4_role,teammate4_role,this,
														menu_selector(MainUILayer::menu_selectcardcallback));
	CCSprite * teammate4_frame = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class1.png"));
	role_frame[4] = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class5_elite.png"));
	teammate4_frame->setPosition(ccp(teammate4_role->getContentSize().width/2,teammate4_role->getContentSize().height/2));
	role_frame[4]->setPosition(ccp(teammate4_role->getContentSize().width/2,teammate4_role->getContentSize().height/2));
	item_role4->addChild(teammate4_frame);
	item_role4->addChild(role_frame[4]);
	role_frame[4]->setTag(111);
	CCMenu* menu_role4 = CCMenu::create(item_role4,NULL);
	menu_role4->setPosition(ccp(553,160));
	team->addChild(menu_role4);
	role_frame[4]->setVisible(false);
	//��Ա4��ʵ��
	text_max[4] = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("arenamain_max.png"));
	text_max[4]->setPosition(ccp(553,91));
	team->addChild(text_max[4]);
	text_level[4] = CCNode::create();
	text_level[4]->setPosition(ccp(553,91));
	team->addChild(text_level[4]);
	str->initWithFormat("%d:%d",CardTeam::sharedCardTeam()->getteammate4_life(),CardTeam::sharedCardTeam()->getteammate4_attack());
	CCLabelTTF* text_lv_value_04 = CCLabelTTF::create(str->m_sString.c_str(),"Arial",17);
	text_lv_value_04->setColor(ccc3(59,199,255));
	text_lv_value_04->setPositionX(0);
	text_level[4]->addChild(text_lv_value_04);
	text_level[4]->setVisible(false);
	//������ʱ��
	this->schedule(schedule_selector(MainUILayer::textlevel_flash),0.8f);
	//����
	CCSprite* mail_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("state_mail.png"));
	CCSprite* mail_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("state_mail.png"));
	CCSprite* mail_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("state_mail.png"));
	CCMenuItemSprite* mailitem = CCMenuItemSprite::create(mail_nor,
															mail_sel,
															mail_disable,
															this,
															menu_selector(MainUILayer::menu_mailcallback));
	CCMenu* mailmenu = CCMenu::create(mailitem,NULL);
	mailmenu->setPosition(ccp(550,270));
	team->addChild(mailmenu);
}
//���ò˵�UI
void MainUILayer::configureMenuUI()
{
	menu = CCNode::create();
	this->addChild(menu);
	//Ӣ��(���ƽ�ɫ)
	CCSprite* card_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* card_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* card_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	CCMenuItemSprite* carditem = CCMenuItemSprite::create(card_nor,
														card_sel,
														card_disable,
														this,
														menu_selector(MainUILayer::menu_cardcallback));
	carditem->setScaleX(1.2f);
	carditem->setScaleY(0.9f);
	CCSprite* text_card = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_card.png"));
	text_card->setPosition(ccp(card_nor->getContentSize().width/2,card_nor->getContentSize().height/2));
	carditem->addChild(text_card);
	//����
	CCSprite* levelup_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* levelup_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* levelup_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	CCMenuItemSprite* levelupitem = CCMenuItemSprite::create(levelup_nor,
															levelup_sel,
															levelup_disable,
															this,
															menu_selector(MainUILayer::menu_cardlevelupcallback));
	levelupitem->setScaleX(1.2f);
	levelupitem->setScaleY(0.9f);
	CCSprite* text_levelup = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_mix.png"));
	text_levelup->setPosition(ccp(levelup_nor->getContentSize().width/2,levelup_nor->getContentSize().height/2));
	levelupitem->addChild(text_levelup);
	
	//����
	CCSprite* tast_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* tast_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* tast_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	CCMenuItemSprite* tastitem = CCMenuItemSprite::create(tast_nor,
														tast_sel,
														tast_disable,
														this,
														menu_selector(MainUILayer::menu_tastcallback));
	tastitem->setScaleX(1.2f);
	tastitem->setScaleY(0.9f);
	CCSprite* text_tast = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_tast.png"));
	text_tast->setPosition(ccp(tast_nor->getContentSize().width/2,tast_nor->getContentSize().height/2));
	tastitem->addChild(text_tast);
	//�浵
	CCSprite* archives_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* archives_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* archives_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	CCMenuItemSprite* archivesitem = CCMenuItemSprite::create(archives_nor,
		archives_sel,
		archives_disable,
		this,
		menu_selector(MainUILayer::menu_archivescallback));
	archivesitem->setScaleX(1.2f);
	archivesitem->setScaleY(0.9f);
	CCLabelTTF* text_archives = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey("text_archives"),"Arial",35);
	text_archives->setPosition(ccp(archives_nor->getContentSize().width/2,archives_nor->getContentSize().height/2));
	archivesitem->addChild(text_archives);
	//�˵�
	CCMenu* menu_col = CCMenu::create(carditem,levelupitem,tastitem,archivesitem,NULL);
	menu_col->alignItemsVerticallyWithPadding(23);
	menu->addChild(menu_col);
	menu_col->setPosition(ccp(visibleSize.width/2,visibleSize.height/2-175));
}
//ѡ��Ӣ�ۻص�����
void MainUILayer::menu_selectcardcallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	for(int i = 0; i < 5; ++i)role_frame[i]->setVisible(false);
	CCMenuItemSprite* item = (CCMenuItemSprite*)pSender;
	CCSprite* frame = (CCSprite*)item->getChildByTag(111);
	frame->setVisible(true);
}

void MainUILayer::menu_mailcallback(CCObject*)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	//ȡ�����ж�ʱ ���Ƴ�team��menu
	this->unscheduleAllSelectors();
	this->removeChild(team);
	this->removeChild(menu);
	team = NULL;
	menu = NULL;
	showMailUI();
}

void MainUILayer::showMailUI()
{
	m_curUI = MAIL_UI;
	mailUI = MailLayer::create();
	this->addChild(mailUI);
}
//���Ӣ�۰�ť�ص��ĺ���
void MainUILayer::menu_cardcallback(CCObject*)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	//ȡ�����ж�ʱ ���Ƴ�team��menu
	this->unscheduleAllSelectors();
	this->removeChild(team);
	this->removeChild(menu);
	team = NULL;
	menu = NULL;
	showCardUI();
}

void MainUILayer::showCardUI()
{
	m_curUI = CARD_UI;
	cardUI = EatedCardLayer::create();
	this->addChild(cardUI);
}

void MainUILayer::menu_cardlevelupcallback(CCObject*)
{
	//�õ���ѡ�еĶ�Ա
	for(int i = 0; i < 5; ++i)
	{
		if(role_frame[i]->isVisible())
		{
			CCUserDefault::sharedUserDefault()->setIntegerForKey("selectedcardindex",i);
			break;
		}
	}
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	//ȡ�����ж�ʱ ���Ƴ�team��menu
	this->unscheduleAllSelectors();
	this->removeChild(team);
	this->removeChild(menu);
	team = NULL;
	menu = NULL;
	showCardLevelupUI();
}
//����
void MainUILayer::showCardLevelupUI()
{
	m_curUI = LEVELUP_UI;
	levelupUI = CardLevelupLayer::create();
	this->addChild(levelupUI);
}

void MainUILayer::menu_tastcallback(CCObject*)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	//ȡ�����ж�ʱ ���Ƴ�team��menu
	this->unscheduleAllSelectors();
	this->removeChild(team);
	this->removeChild(menu);
	team = NULL;
	menu = NULL;
	showTastUI();
}

void MainUILayer::showTastUI()
{
	m_curUI = TAST_UI;
	tastUI = TastLayer::create();
	this->addChild(tastUI);
}

void MainUILayer::menu_archivescallback(CCObject*)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	Archives::sharedArchives()->setArchives();
	DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("text_archives_tips"));
	this->addChild(layer);
}

void MainUILayer::textlevel_flash(float)
{
	for(int i = 0; i < 5; ++i)
	{
		text_max[i]->setVisible(!text_max[i]->isVisible());
		text_level[i]->setVisible(!text_level[i]->isVisible());
	}
}


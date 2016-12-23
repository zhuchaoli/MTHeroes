#include "ArenaLayer.h"
#include "AppMacros.h"
#include "AppStringFile.h"
#include "BattleLayer.h"
#include "Hero.h"

bool ArenaLayer::init()
{
	if(!CCLayer::init())return false;
	pos_x[0] = pos_x[3] = 160;
	pos_x[2] = pos_x[4] = 485;
	pos_x[1] = 320;
	pos_y[0] = pos_y[1] = pos_y[2] = 550;
	pos_y[3] = pos_y[4] = 390;
	m_curUI = ARENA_UI;
	arenalistlayer = NULL;
	initframe();
	//ע����������
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(ArenaLayer::return_arena),"ReturnArena",NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(ArenaLayer::return_lineup),"ReturnLineup2",NULL);
	return true;
}

void ArenaLayer::initframe()
{
	//�м䱳��
	listbase = CCSprite::create("ui/listbase_1.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(ccp(visibleSize.width/2,400));
	this->addChild(listbase,1);
	//��ʼ���б�
	initList();
	//��������
	CCSprite* background = CCSprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(ccp(visibleSize.width/2,760));
	this->addChild(background,3);
	//�ײ�����
	CCSprite* bottom_list = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bottom_list.jpg"));
	bottom_list->setPosition(ccp(visibleSize.width/2,bottom_list->getContentSize().height/2));
	this->addChild(bottom_list,3);
	//���ⱳ��
	CCSprite* middletitlebase = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("middletitlebase.png"));
	middletitlebase->setPosition(ccp(visibleSize.width/2,700));
	this->addChild(middletitlebase,3);
	//����
	title_custom_arena = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("titlename_arena.png"));
	title_custom_arena->setPosition(ccp(visibleSize.width/2,690));
	this->addChild(title_custom_arena,4);
}

void ArenaLayer::initList()
{
	arenalistlayer = ArenaListLayer::create();
	arenalistlayer->setPosition(ccp(20,160));
	this->addChild(arenalistlayer,2);
}

void ArenaLayer::return_arena(CCObject*)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	this->removeChild(title_custom_lineup);
	title_custom_lineup = NULL;
	this->removeChild(menu_left_return);
	this->removeChild(lineup_content);
	//���¸��±���
	listbase->setTexture(CCTextureCache::sharedTextureCache()->addImage("ui/listbase_1.jpg"));
	//���¼��ر���
	title_custom_arena = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("titlename_arena.png"));
	title_custom_arena->setPosition(ccp(visibleSize.width/2,690));
	this->addChild(title_custom_arena,4);
	initList();//���¼����б�
	m_curUI = ARENA_UI;
}

void ArenaLayer::return_lineup(CCObject*)
{
	this->removeChild(arenalistlayer);
	arenalistlayer = NULL;
	this->removeChild(title_custom_arena);
	//���¸��±���
	listbase->setTexture(CCTextureCache::sharedTextureCache()->addImage("ui/confirmlinebase.jpg"));
	listbase->setScaleY(0.99f);
	//���ر���
	title_custom_lineup = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("titlename_lineup.png"));
	title_custom_lineup->setPosition(ccp(visibleSize.width/2,690));
	this->addChild(title_custom_lineup,4);
	//���ذ�ť
	CCSprite* button_left_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_0.png"));
	CCSprite* button_left_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_1.png"));
	CCSprite* button_left_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_2.png"));
	CCMenuItemSprite* button_left_item = CCMenuItemSprite::create(button_left_nor,
																	button_left_sel,
																	button_left_disable,
																	this,
																	menu_selector(ArenaLayer::return_arena));
	CCSprite* text_return = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_return.png"));
	text_return->setPosition(ccp(button_left_nor->getContentSize().width/2-15,button_left_nor->getContentSize().height/2));
	button_left_item->addChild(text_return);
	menu_left_return = CCMenu::create(button_left_item,NULL);
	menu_left_return->setPosition(ccp(button_left_nor->getContentSize().width/2-10,687));
	this->addChild(menu_left_return,4);
	//���ض���
	lineup_content = CCNode::create();
	CCString* str = CCString::create("");
	//�ӳ�
	CCNode* cardcap = CCNode::create();
	CCSprite* cardcap_frame = CCSprite::createWithSpriteFrameName("bigcard_frame_class4_elite.png");
	cardcap->addChild(cardcap_frame);
	str->initWithFormat("captain_role_big");
	CCSprite* cardcap_content = CCSprite::createWithSpriteFrameName(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString));
	cardcap->addChild(cardcap_content);
	CCSprite* cardcap_occupation_base = CCSprite::createWithSpriteFrameName("icon_occupation_base_elite.png");
	cardcap->addChild(cardcap_occupation_base);
	CCSprite* cardcap_occupation = CCSprite::createWithSpriteFrameName("icon_occupation_warrior_button.png");
	cardcap_occupation->setScale(2.0f);
	cardcap_occupation->setPosition(ccp(61,-73));
	cardcap->addChild(cardcap_occupation);
	cardcap->setScale(0.6f);
	cardcap->setPosition(ccp(pos_x[0],pos_y[0]));
	lineup_content->addChild(cardcap);
	//�ӳ��ı�־
	CCSprite* nameplate_cap = CCSprite::createWithSpriteFrameName("nameplate_captain.png");
	nameplate_cap->setPosition(ccp(110,620));
	lineup_content->addChild(nameplate_cap);
	//��Ա
	for(int i = 1; i < 5; ++i)
	{
		CCNode* card = CCNode::create();
		CCSprite* card_frame = CCSprite::createWithSpriteFrameName("bigcard_frame_class4_elite.png");
		card->addChild(card_frame);
		str->initWithFormat("teammate%d_role_big",i);
		CCSprite* card_content = CCSprite::createWithSpriteFrameName(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString));
		card->addChild(card_content);
		CCSprite* card_occupation_base = CCSprite::createWithSpriteFrameName("icon_occupation_base_elite.png");
		card->addChild(card_occupation_base);
		CCSprite* card_occupation = CCSprite::createWithSpriteFrameName("icon_occupation_shaman_button.png");
		card_occupation->setScale(2.0f);
		card_occupation->setPosition(ccp(61,-73));
		card->addChild(card_occupation);
		card->setScale(0.6f);
		card->setPosition(ccp(pos_x[i],pos_y[i]));
		lineup_content->addChild(card);
	}
	//�Ŷ�ʵ��
	CCSprite* teamlv_text = CCSprite::createWithSpriteFrameName("teamlv.png");
	teamlv_text->setScale(1.1f);
	teamlv_text->setPosition(ccp(250,262));
	lineup_content->addChild(teamlv_text);
	str->initWithFormat("%d",Hero::sharedHero()->getTeamLv());
	CCLabelTTF* teamlv = CCLabelTTF::create(str->m_sString.c_str(),"Arial",33);
	teamlv->setPosition(ccp(380,262));
	lineup_content->addChild(teamlv);
	//��ʼս����ť
	CCSprite* button_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* button_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* button_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	CCMenuItemSprite* button_start_item = CCMenuItemSprite::create(button_nor,
																button_sel,
																button_disable,
																this,
																menu_selector(ArenaLayer::menu_start_battle));
	CCSprite* text_starin = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_starin.png"));
	text_starin->setPosition(ccp(button_nor->getContentSize().width/2,button_nor->getContentSize().height/2));
	button_start_item->addChild(text_starin);
	CCMenu* menu_start = CCMenu::create(button_start_item,NULL);
	menu_start->setPosition(ccp(visibleSize.width/2,190));
	lineup_content->addChild(menu_start);
	this->addChild(lineup_content,5);
	m_curUI = LINEUP_UI;
}

void ArenaLayer::menu_start_battle(CCObject*)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	//ʹ��pushScene
	CCDirector::sharedDirector()->pushScene(BattleLayer::scene());
}
//���ص���������
void ArenaLayer::restoreToArenaUI()
{
	if(m_curUI == LINEUP_UI)
	{
		return_arena(NULL);
	}
}

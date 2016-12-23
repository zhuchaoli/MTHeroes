#include "TastLayer.h"
#include "TastListLayer.h"
#include "AppMacros.h"

bool TastLayer::init()
{
	if(!CCLayer::init())return false;
	initframe();
	return true;
}

void TastLayer::initframe()
{
	//�Ϸ�����
	CCSprite* listbase = CCSprite::create("ui/listbase_1.jpg");
	listbase->setScale(1.4f);
	listbase->setPosition(ccp(visibleSize.width/2,410));
	this->addChild(listbase);
	//��ʼ�������б�
	initTastList();
	//����
	CCSprite* background = CCSprite::create("ui/background_2.jpg");
	background->setScale(1.26f);
	background->setPosition(ccp(visibleSize.width/2,760));
	this->addChild(background);
	//�ײ�����
	CCSprite* bottom_list = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bottom_list.jpg"));
	bottom_list->setPosition(ccp(visibleSize.width/2,bottom_list->getContentSize().height/2));
	this->addChild(bottom_list);
	//�������ֱ���
	CCSprite* middletitlebase = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("middletitlebase.png"));
	middletitlebase->setPosition(ccp(visibleSize.width/2,700));
	this->addChild(middletitlebase);
	//��������
	CCSprite* titlenamemycard = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("titlename_task.png"));
	titlenamemycard->setPosition(ccp(visibleSize.width/2,690));
	this->addChild(titlenamemycard);
	//���ذ�ť
	CCSprite* button_left_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_0.png"));
	CCSprite* button_left_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_1.png"));
	CCSprite* button_left_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_left_2.png"));
	CCMenuItemSprite* button_left_item = CCMenuItemSprite::create(button_left_nor,
																	button_left_sel,
																	button_left_disable,
																	this,
																	menu_selector(TastLayer::menu_returncallback));
	CCSprite* text_return = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_return.png"));
	text_return->setPosition(ccp(button_left_nor->getContentSize().width/2-15,button_left_nor->getContentSize().height/2));
	button_left_item->addChild(text_return);
	CCMenu* button_left_menu = CCMenu::create(button_left_item,NULL);
	button_left_menu->setPosition(ccp(button_left_nor->getContentSize().width/2-10,687));
	this->addChild(button_left_menu);
}

void TastLayer::initTastList()
{
	//Ҫ���ж� �Ƿ���Ҫ����
	time_t t = time(NULL);
	int sec = CCUserDefault::sharedUserDefault()->getIntegerForKey("systime_sec2",0);
	if(sec == 0 || t - sec >= 20)
	{
		TastListLayer* layer = TastListLayer::create();
		layer->setPosition(ccp(20,160));
		this->addChild(layer);
		//��¼��ǰ��ȡʱ��
		CCUserDefault::sharedUserDefault()->setIntegerForKey("systime_sec2",t);
	}
}

void TastLayer::menu_returncallback(CCObject*)
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification("ReturnToMain");
}
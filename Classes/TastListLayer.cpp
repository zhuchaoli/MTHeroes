#include "TastListLayer.h"
#include "AppMacros.h"
#include "CardTeam.h"
#include "Hero.h"
#include "AppStringFile.h"
#include "DialogStringLayer.h"

bool TastListLayer::init()
{
	if(!CCLayer::init())return false;
	for(int i = 0; i < 5; ++i)
	{
		isTouched[i] = false;
	}
	srand(time(NULL));
	randsum = rand()%6;
	CCTableView* tableview = CCTableView::create(this,CCSizeMake(600,500));
	tableview->setDirection(kCCScrollViewDirectionVertical);//������ֱ����
	tableview->setDelegate(this);
	this->addChild(tableview);
	tableview->setVerticalFillOrder(kCCTableViewFillTopDown);
	tableview->reloadData();//�����е�����ȥˢ�����е�cell
	return true;
}

void TastListLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	int index = cell->getIdx();
	DialogStringLayer* dlg;
	if(isTouched[index])return;
	isTouched[index] = true;//���ñ������
	if(index == 0)//���
	{
		dlg = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("tast_tips0"));
		//��Ҹ���
		Hero::sharedHero()->setMoney(Hero::sharedHero()->getMoney()+500);
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMoneyAndDiamon");
	}
	else if(index == 1)//��ʯ
	{
		dlg = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("tast_tips1"));
		Hero::sharedHero()->setDiamond(Hero::sharedHero()->getDiamond()+50);
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMoneyAndDiamon");
	}
	else if(index == 2)//����
	{
		dlg = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("tast_tips2"));
		int strengthvar = Hero::sharedHero()->getStrength()+50;
		strengthvar = strengthvar > 100?100:strengthvar;
		Hero::sharedHero()->setStrength(strengthvar);
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateStrengthAndExp");
	}
	else if(index == 3)//����
	{
		dlg = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("tast_tips3"));
		Hero::sharedHero()->setExp(Hero::sharedHero()->getExp()+30);
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateStrengthAndExp");
	}
	else if(index == 4)//���Ӣ��
	{
		dlg = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("tast_tips4"));
		CardTeam::sharedCardTeam()->setEatedCardCountByKey(randsum,2);
	}
	this->getParent()->addChild(dlg);
	cell->getChildByTag(777)->removeChildByTag(888);
	//�����ұ߱�־
	cell->getChildByTag(777)->getChildByTag(999)->setVisible(false);
	cell->getChildByTag(777)->getChildByTag(1000)->setVisible(true);
}

//����Ԫ�����óߴ�
CCSize TastListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return CCSizeMake(565,110);
}
//����Ԫ���������ʱ���õĺ���
CCTableViewCell* TastListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	
	CCTableViewCell* cell = new CCTableViewCell();
	cell->autorelease();////////
	CCNode* item_node = getItemNode(idx);
	item_node->setAnchorPoint(ccp(0,0));
	item_node->setPosition(ccp(0,0));
	item_node->setTag(777);
	cell->addChild(item_node);
	return cell;
}
//���õ�Ԫ��ĸ���
unsigned int TastListLayer::numberOfCellsInTableView(CCTableView *table)
{
	return 5;
}

CCNode* TastListLayer::getItemNode(int i)
{
	CCNode* item = CCNode::create();
	//��Ԫ�񱳾�
	CCSprite* item_bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("listbutton_base1_0.png"));
	item_bk->setAnchorPoint(ccp(0,0));
	item_bk->setPosition(ccp(20,0));
	item->addChild(item_bk);
	if(!isTouched[i])//
	{
		CCSprite* item_h1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("listbutton_base1_1.png"));
		item_h1->setAnchorPoint(ccp(0,0));
		item_h1->setPosition(ccp(20,0));
		item_h1->setScale(2.0f);
		item_h1->setTag(888);
		item->addChild(item_h1);
	}
	//���ͼƬ��
	CCSprite* item_frame =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class5.png"));
	item_frame->setAnchorPoint(ccp(0,0));
	item_frame->setPosition(ccp(30,15));
	item_frame->setScale(0.9f);
	item->addChild(item_frame);
	//���ͼƬ
	CCSprite* item_img;
	CCString* str = CCString::create("");
	if(i == 4)//�������һ������Ӣ��
	{
		str->initWithFormat("eatedcard%d",randsum);
		item_img = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString));
	}
	else
	{
		str->initWithFormat("tast_leftimg%d",i);
		item_img = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString)));
	}
	item_img->setPosition(ccp(30,15));
	item_img->setAnchorPoint(ccp(0,0));
	item_img->setScale(0.9f);
	item->addChild(item_img);
	//�м��ı�
	str->initWithFormat("tast_tittle%d",i);
	CCLabelTTF* item_tittle = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",25);
	item_tittle->setAnchorPoint(ccp(0,0));
	item_tittle->setPosition(ccp(140,75));
	item->addChild(item_tittle);
	str->initWithFormat("tast_text%d",i);
	CCLabelTTF* item_text = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",20);
	item_text->setAnchorPoint(ccp(0,0));
	item_text->setPosition(ccp(140,35));
	item->addChild(item_text);
	//�ұ߱�־
	CCSprite* item_sign1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sign_underway.png"));
	item_sign1->setAnchorPoint(ccp(0,0));
	item_sign1->setTag(999);
	item_sign1->setPosition(ccp(430,30));
	item->addChild(item_sign1);
	
	CCSprite* item_sign2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sign_complete.png"));
	item_sign2->setAnchorPoint(ccp(0,0));
	item_sign2->setTag(1000);
	item_sign2->setPosition(ccp(430,30));
	
	item->addChild(item_sign2);
	if(!isTouched[i])
	{
		item_sign1->setVisible(true);
		item_sign2->setVisible(false);
	}
	else
	{
		item_sign1->setVisible(false);
		item_sign2->setVisible(true);
	}
	return item;
}


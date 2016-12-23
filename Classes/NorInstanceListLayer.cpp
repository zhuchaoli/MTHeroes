#include "NorInstanceListLayer.h"
#include "AppMacros.h"
#include "GuanQiaState.h"
#include "DialogStringLayer.h"
#include "Hero.h"
#include "AppStringFile.h"

bool NorInstanceListLayer::init()
{
	if(!CCLayer::init())return false;
	CCTableView* tableview = CCTableView::create(this,CCSizeMake(600,500));
	tableview->setDirection(kCCScrollViewDirectionVertical);//������ֱ����
	tableview->setDelegate(this);
	this->addChild(tableview);
	tableview->setVerticalFillOrder(kCCTableViewFillTopDown);
	tableview->reloadData();//�����е�����ȥˢ�����е�cell
	tableview->setTag(0);
	return true;
}

void NorInstanceListLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	//�ж������Ƿ�
	if(Hero::sharedHero()->getStrength() < 5)
	{
		DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("instance_strength_tips"));
		this->getParent()->addChild(layer,4);
		return;
	}
	int index = cell->getIdx();
	CCUserDefault::sharedUserDefault()->setIntegerForKey("selectedguanqia",index);
	if(GuanQiaState::sharedGuanQiaState()->isComplete_GuanQia[index])
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification("ReturnLineup");
	}
	else
	{
		DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("instance_tips"));
		this->getParent()->addChild(layer,4);
	}
}

//����Ԫ�����óߴ�
CCSize NorInstanceListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return CCSizeMake(565,110);
}
//����Ԫ���������ʱ���õĺ���
CCTableViewCell* NorInstanceListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCTableViewCell* cell = new CCTableViewCell();
	cell->autorelease();////////
	CCNode* item_node = getItemNode(idx);
	item_node->setAnchorPoint(ccp(0,0));
	item_node->setPosition(ccp(0,0));
	item_node->setTag(100);
	cell->addChild(item_node);
	return cell;
}
//���õ�Ԫ��ĸ���
unsigned int NorInstanceListLayer::numberOfCellsInTableView(CCTableView *table)
{
	return 21;
}

CCNode* NorInstanceListLayer::getItemNode(int i)
{
	CCNode* item = CCNode::create();
	//��Ԫ�񱳾�
	CCSprite* item_bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_rank_hero_0.png"));
	item_bk->setAnchorPoint(ccp(0,0));
	item_bk->setPosition(ccp(20,0));
	item->addChild(item_bk);
	//�ؿ�
	CCString* str = CCString::createWithFormat("normal_instance_%02d",i);
	CCLabelTTF* item_guanqia = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",30);
	item_guanqia->setAnchorPoint(ccp(0,0));
	item_guanqia->setPosition(ccp(45,20));
	item->addChild(item_guanqia);
	//ͨ��״̬
	CCSprite* item_state;
	if(GuanQiaState::sharedGuanQiaState()->isComplete_GuanQia[i])
	{
		item_state = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("state_complete.png"));
	}
	else
	{
		item_state = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("state_new.png"));
	}
	item_state->setAnchorPoint(ccp(0,0));
	item_state->setPosition(ccp(20,60));
	item->addChild(item_state);
	return item;
}


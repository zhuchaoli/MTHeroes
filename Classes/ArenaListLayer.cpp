#include "ArenaListLayer.h"
#include "AppMacros.h"
#include "GuanQiaState.h"
#include "DialogStringLayer.h"
#include "Hero.h"
#include "AppStringFile.h"

bool ArenaListLayer::init()
{
	if(!CCLayer::init())return false;
	CCTableView* tableview = CCTableView::create(this,CCSizeMake(600,500));
	tableview->setDirection(kCCScrollViewDirectionVertical);//设置竖直滚动
	tableview->setDelegate(this);
	this->addChild(tableview);
	tableview->setVerticalFillOrder(kCCTableViewFillTopDown);
	tableview->reloadData();//用现有的配置去刷新所有的cell
	tableview->setTag(0);
	return true;
}

void ArenaListLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	//判断体力是否够
	if(Hero::sharedHero()->getStrength() < 5)
	{
		DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("arena_strength_tips"));
		this->getParent()->addChild(layer,4);
		return;
	}
	int index = cell->getIdx();
	CCUserDefault::sharedUserDefault()->setIntegerForKey("selectedguanqia",index);
	//判断当前关卡是否已经通关
	if(GuanQiaState::sharedGuanQiaState()->isComplete_GuanQia[index])
	{
		DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("arena_tips"));
		this->getParent()->addChild(layer,4);
	}
	else if(Hero::sharedHero()->getCurChallengeGQ() == index)
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification("ReturnLineup2");
	}
	else
	{
		DialogStringLayer* layer = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("arena_waring_tips"));
		this->getParent()->addChild(layer,4);
	}
}

//给单元格设置尺寸
CCSize ArenaListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return CCSizeMake(565,110);
}
//给单元格填充内容时调用的函数
CCTableViewCell* ArenaListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
//设置单元格的个数
unsigned int ArenaListLayer::numberOfCellsInTableView(CCTableView *table)
{
	return 21;
}

CCNode* ArenaListLayer::getItemNode(int i)
{
	CCNode* item = CCNode::create();
	//单元格背景
	CCSprite* item_bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_rank_hero_1.png"));
	item_bk->setAnchorPoint(ccp(0,0));
	item_bk->setPosition(ccp(20,0));
	item->addChild(item_bk);
	//关卡
	CCString* str = CCString::createWithFormat("normal_instance_%02d",i);
	CCLabelTTF* item_guanqia = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",30);
	item_guanqia->setAnchorPoint(ccp(0,0));
	item_guanqia->setPosition(ccp(45,20));
	item->addChild(item_guanqia);
	//通关状态
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


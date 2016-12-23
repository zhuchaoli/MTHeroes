#include "MoreListLayer.h"
#include "AppMacros.h"
#include "AppStringFile.h"

bool MoreListLayer::init()
{
	if(!CCLayer::init())return false;
	CCTableView* tableview = CCTableView::create(this,CCSizeMake(600,500));
	tableview->setDirection(kCCScrollViewDirectionVertical);//设置竖直滚动
	tableview->setDelegate(this);
	this->addChild(tableview);
	tableview->setVerticalFillOrder(kCCTableViewFillTopDown);
	tableview->reloadData();//用现有的配置去刷新所有的cell
	return true;
}

//给单元格设置尺寸
CCSize MoreListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return CCSizeMake(565,110);
}
//给单元格填充内容时调用的函数
CCTableViewCell* MoreListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCTableViewCell* cell = new CCTableViewCell();
	cell->autorelease();////////
	CCNode* item_node = getItemNode(idx);
	item_node->setAnchorPoint(ccp(0,0));
	item_node->setPosition(ccp(0,0));
	cell->addChild(item_node);
	return cell;
}
//设置单元格的个数
unsigned int MoreListLayer::numberOfCellsInTableView(CCTableView *table)
{
	return 13;
}

CCNode* MoreListLayer::getItemNode(int i)
{
	CCNode* item = CCNode::create();
	//单元格背景
	CCSprite* item_bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_public_rank2_0.png"));
	item_bk->setAnchorPoint(ccp(0,0));
	item_bk->setPosition(ccp(20,0));
	item->addChild(item_bk);
	//攻略背景
	CCSprite* more_bk =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class2.png"));
	more_bk->setAnchorPoint(ccp(0,0));
	more_bk->setPosition(ccp(28,2));
	item->addChild(more_bk);
	//攻略文本
	const char* gonglue = AppStringFile::sharedAppStringFile()->getStringForKey("more_text");
	CCString* str = CCString::createWithFormat("%s%d",gonglue,i+1);
	CCLabelTTF* more_text = CCLabelTTF::create(str->m_sString.c_str(),"Arial",27);
	more_text->setPosition(ccp(more_bk->getContentSize().width/2,more_bk->getContentSize().height/2));
	more_text->setColor(ccc3(255,255,0));
	more_bk->addChild(more_text);
	//攻略内容
	str->initWithFormat("more%d",i);
	CCLabelTTF* more_content = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",25);
	more_content->setAnchorPoint(ccp(0,0));
	more_content->setPosition(ccp(130,40));
	item->addChild(more_content);
	return item;
}


#include "MoreListLayer.h"
#include "AppMacros.h"
#include "AppStringFile.h"

bool MoreListLayer::init()
{
	if(!CCLayer::init())return false;
	CCTableView* tableview = CCTableView::create(this,CCSizeMake(600,500));
	tableview->setDirection(kCCScrollViewDirectionVertical);//������ֱ����
	tableview->setDelegate(this);
	this->addChild(tableview);
	tableview->setVerticalFillOrder(kCCTableViewFillTopDown);
	tableview->reloadData();//�����е�����ȥˢ�����е�cell
	return true;
}

//����Ԫ�����óߴ�
CCSize MoreListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return CCSizeMake(565,110);
}
//����Ԫ���������ʱ���õĺ���
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
//���õ�Ԫ��ĸ���
unsigned int MoreListLayer::numberOfCellsInTableView(CCTableView *table)
{
	return 13;
}

CCNode* MoreListLayer::getItemNode(int i)
{
	CCNode* item = CCNode::create();
	//��Ԫ�񱳾�
	CCSprite* item_bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_public_rank2_0.png"));
	item_bk->setAnchorPoint(ccp(0,0));
	item_bk->setPosition(ccp(20,0));
	item->addChild(item_bk);
	//���Ա���
	CCSprite* more_bk =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class2.png"));
	more_bk->setAnchorPoint(ccp(0,0));
	more_bk->setPosition(ccp(28,2));
	item->addChild(more_bk);
	//�����ı�
	const char* gonglue = AppStringFile::sharedAppStringFile()->getStringForKey("more_text");
	CCString* str = CCString::createWithFormat("%s%d",gonglue,i+1);
	CCLabelTTF* more_text = CCLabelTTF::create(str->m_sString.c_str(),"Arial",27);
	more_text->setPosition(ccp(more_bk->getContentSize().width/2,more_bk->getContentSize().height/2));
	more_text->setColor(ccc3(255,255,0));
	more_bk->addChild(more_text);
	//��������
	str->initWithFormat("more%d",i);
	CCLabelTTF* more_content = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",25);
	more_content->setAnchorPoint(ccp(0,0));
	more_content->setPosition(ccp(130,40));
	item->addChild(more_content);
	return item;
}


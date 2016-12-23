#include "EatedCardListLayer.h"
#include "AppMacros.h"
#include "CardTeam.h"
#include "AppStringFile.h"

bool EatedCardListLayer::init()
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
CCSize EatedCardListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return CCSizeMake(565,110);
}
//����Ԫ���������ʱ���õĺ���
CCTableViewCell* EatedCardListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
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
unsigned int EatedCardListLayer::numberOfCellsInTableView(CCTableView *table)
{
	return 6;
}

CCNode* EatedCardListLayer::getItemNode(int i)
{
	CCNode* item = CCNode::create();
	//��Ԫ�񱳾�
	CCSprite* item_bk = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_public_rank_0.png"));
	item_bk->setAnchorPoint(ccp(0,0));
	item_bk->setPosition(ccp(20,0));
	item->addChild(item_bk);
	//���Ʊ���
	CCSprite* item_eatedcard_bk =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_base_class1.png"));
	item_eatedcard_bk->setScale(1.1f);
	item_eatedcard_bk->setAnchorPoint(ccp(0,0));
	item_eatedcard_bk->setPosition(ccp(15,2));
	item->addChild(item_eatedcard_bk);
	//����
	CCString* str = CCString::createWithFormat("eatedcard%d",i);
	CCSprite* item_eatedcard = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString));
	item_eatedcard->setAnchorPoint(ccp(0,0));
	item_eatedcard->setPosition(ccp(15,2));
	item->addChild(item_eatedcard);
	CCSprite* item_eatedcard_frame =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class3_elite.png"));
	item_eatedcard_frame->setAnchorPoint(ccp(0,0));
	item_eatedcard_frame->setPosition(ccp(15,2));
	item->addChild(item_eatedcard_frame);
	//���Ƶ�����
	str->initWithFormat("eatedcard%d_name",i);
	CCLabelTTF* item_eatedcard_name = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",25);
	item_eatedcard_name->setAnchorPoint(ccp(0,0));
	item_eatedcard_name->setPosition(ccp(160,60));
	item->addChild(item_eatedcard_name);
	//���Ƶ�ͼ��
	CCSprite* item_occupation = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_occupation_warrior_button.png"));
	item_occupation->setAnchorPoint(ccp(0,0));
	item_occupation->setScale(1.2f);
	item_occupation->setPosition(ccp(115,50));
	item->addChild(item_occupation);
	//������
	str->initWithFormat("eatedcard%d_addlife",i);
	CCLabelTTF* item_addlife = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",20);
	item_addlife->setAnchorPoint(ccp(0,0));
	item_addlife->setPosition(ccp(160,20));
	item->addChild(item_addlife);
	//�ӹ���
	str->initWithFormat("eatedcard%d_addattack",i);
	CCLabelTTF* item_addattack = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",20);
	item_addattack->setAnchorPoint(ccp(0,0));
	item_addattack->setPosition(ccp(280,20));
	item->addChild(item_addattack);
	//���Ľ��
	CCSprite* money_icon = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_bigcoin.png"));
	money_icon->setScale(0.3f);
	money_icon->setAnchorPoint(ccp(0,0));
	money_icon->setPosition(ccp(370,18));
	item->addChild(money_icon);
	str->initWithFormat("eatedcard%d_submoney",i);
	CCLabelTTF* item_submoney = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",20);
	item_submoney->setAnchorPoint(ccp(0,0));
	item_submoney->setPosition(ccp(410,20));
	item->addChild(item_submoney);
	//���ķ�ʯ
	CCSprite* diamon_icon = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_diamond1.png"));
	diamon_icon->setScale(0.3f);
	diamon_icon->setAnchorPoint(ccp(0,0));
	diamon_icon->setPosition(ccp(490,18));
	item->addChild(diamon_icon);
	str->initWithFormat("eatedcard%d_subdiamon",i);
	CCLabelTTF* item_subdiamon = CCLabelTTF::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString),"Arial",20);
	item_subdiamon->setAnchorPoint(ccp(0,0));
	item_subdiamon->setPosition(ccp(530,20));
	item->addChild(item_subdiamon);
	//��������
	str->initWithFormat("X %d",CardTeam::sharedCardTeam()->getEatedCardCountByKey(i));
	CCLabelTTF* item_cardcount = CCLabelTTF::create(str->m_sString.c_str(),"Arial",35);
	item_cardcount->setColor(ccc3(255,255,0));
	item_cardcount->setAnchorPoint(ccp(0,0));
	item_cardcount->setPosition(ccp(450,48));
	item->addChild(item_cardcount);
	return item;
}


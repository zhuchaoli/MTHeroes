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
	tableview->setDirection(kCCScrollViewDirectionVertical);//设置竖直滚动
	tableview->setDelegate(this);
	this->addChild(tableview);
	tableview->setVerticalFillOrder(kCCTableViewFillTopDown);
	tableview->reloadData();//用现有的配置去刷新所有的cell
	return true;
}

void TastListLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	int index = cell->getIdx();
	DialogStringLayer* dlg;
	if(isTouched[index])return;
	isTouched[index] = true;//设置被点击了
	if(index == 0)//金币
	{
		dlg = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("tast_tips0"));
		//金币更新
		Hero::sharedHero()->setMoney(Hero::sharedHero()->getMoney()+500);
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMoneyAndDiamon");
	}
	else if(index == 1)//符石
	{
		dlg = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("tast_tips1"));
		Hero::sharedHero()->setDiamond(Hero::sharedHero()->getDiamond()+50);
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateMoneyAndDiamon");
	}
	else if(index == 2)//体力
	{
		dlg = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("tast_tips2"));
		int strengthvar = Hero::sharedHero()->getStrength()+50;
		strengthvar = strengthvar > 100?100:strengthvar;
		Hero::sharedHero()->setStrength(strengthvar);
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateStrengthAndExp");
	}
	else if(index == 3)//经验
	{
		dlg = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("tast_tips3"));
		Hero::sharedHero()->setExp(Hero::sharedHero()->getExp()+30);
		CCNotificationCenter::sharedNotificationCenter()->postNotification("updateStrengthAndExp");
	}
	else if(index == 4)//随机英雄
	{
		dlg = DialogStringLayer::create(AppStringFile::sharedAppStringFile()->getStringForKey("tast_tips4"));
		CardTeam::sharedCardTeam()->setEatedCardCountByKey(randsum,2);
	}
	this->getParent()->addChild(dlg);
	cell->getChildByTag(777)->removeChildByTag(888);
	//更新右边标志
	cell->getChildByTag(777)->getChildByTag(999)->setVisible(false);
	cell->getChildByTag(777)->getChildByTag(1000)->setVisible(true);
}

//给单元格设置尺寸
CCSize TastListLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	return CCSizeMake(565,110);
}
//给单元格填充内容时调用的函数
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
//设置单元格的个数
unsigned int TastListLayer::numberOfCellsInTableView(CCTableView *table)
{
	return 5;
}

CCNode* TastListLayer::getItemNode(int i)
{
	CCNode* item = CCNode::create();
	//单元格背景
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
	//左边图片框
	CCSprite* item_frame =  CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("littlecard_frame_class5.png"));
	item_frame->setAnchorPoint(ccp(0,0));
	item_frame->setPosition(ccp(30,15));
	item_frame->setScale(0.9f);
	item->addChild(item_frame);
	//左边图片
	CCSprite* item_img;
	CCString* str = CCString::create("");
	if(i == 4)//随机产生一个吞噬英雄
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
	//中间文本
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
	//右边标志
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


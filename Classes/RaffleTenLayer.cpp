#include "RaffleTenLayer.h"
#include "AppMacros.h"
#include "AppStringFile.h"

int* RaffleTenLayer::pcards = NULL;

CCScene* RaffleTenLayer::scene(int* cards)
{
	pcards = cards;
	CCScene* scene = CCScene::create();
	RaffleTenLayer* layer = RaffleTenLayer::create();
	scene->addChild(layer);
	return scene;
}

bool RaffleTenLayer::init()
{
	if(!CCLayer::init())return false;
	m_cardth = 0;
	m_posx[0] = m_posx[9] = 100;
	m_posx[1] = m_posx[8] = 210;
	m_posx[2] = m_posx[7] = 320;
	m_posx[3] = m_posx[6] = 430;
	m_posx[4] = m_posx[5] = 540;
	m_posy[0] = m_posy[1] = m_posy[2] = m_posy[3] = m_posy[4] = 850;
	m_posy[5] = m_posy[6] = m_posy[7] = m_posy[8] = m_posy[9] = 710;
	initBK();
	return true;
}

void RaffleTenLayer::initBK()
{
	//背景
	CCSprite* bk = CCSprite::create("ui/backgroud_raffleanimation.jpg");
	bk->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	bk->setScale(2.0f);
	this->addChild(bk);
	//地上的光
	raffle_daguang_flash = CCSprite::createWithSpriteFrameName("raffle_daguang00.png");
	raffle_daguang_flash->setScale(2.5f);
	raffle_daguang_flash->setPosition(ccp(visibleSize.width/2,290));
	this->addChild(raffle_daguang_flash);
	raffle_daguang_flash->runAction(CCBlink::create(4.0f,3));
	//垂直光源
	raffle_guang = CCSprite::createWithSpriteFrameName("raffle_guang00.png");
	raffle_guang->setScale(0.2f);
	raffle_guang->setPosition(ccp(visibleSize.width/2,310));
	this->addChild(raffle_guang);
	raffle_guang->runAction(CCSequence::create(CCScaleTo::create(0.3f,1.2f),
		CCCallFunc::create(this,callfunc_selector(RaffleTenLayer::show_chuizhiguang)),NULL));
}

void RaffleTenLayer::menu_comfirm_callback(CCObject*)
{
	CCDirector::sharedDirector()->popScene();
}

void RaffleTenLayer::show_chuizhiguang()
{
	//照出来的垂直光
	chuizhiguang = CCNode::create();
	chuizhiguang->setPosition(ccp(320,380));
	this->addChild(chuizhiguang);
	CCProgressTimer* guangwai = CCProgressTimer::create(CCSprite::createWithSpriteFrameName("raffle_guangwai00.png"));
	chuizhiguang->addChild(guangwai);
	guangwai->setType(kCCProgressTimerTypeBar);//设置进度条为水平
	guangwai->setBarChangeRate(ccp(0,1));//（0,1）表示纵方向
	guangwai->setMidpoint(ccp(0,0));//设置进度条从左到右 从0开始
	guangwai->runAction(CCProgressTo::create(0.3f,100));
	chuizhiguang->runAction(CCSequence::create(CCDelayTime::create(0.3f),
		CCCallFunc::create(this,callfunc_selector(RaffleTenLayer::chuizhiguang_done)),NULL));
}

void RaffleTenLayer::chuizhiguang_done()
{
	this->removeChild(chuizhiguang);
	this->removeChild(raffle_guang);
	//添加底部的八卦
	raffle_he_flash = CCSprite::createWithSpriteFrameName("raffle_he00.png");
	raffle_he_flash->setPosition(ccp(320,330));
	this->addChild(raffle_he_flash);
	raffle_he_flash->runAction(CCSequence::create(CCScaleTo::create(0.5f,2.0f),
		                             CCScaleTo::create(0.5f,1.0f),
									 CCScaleTo::create(0.5f,2.0f),
									 CCScaleTo::create(0.5f,1.0f),
									 CCScaleTo::create(0.5f,2.0f),
									 CCScaleTo::create(0.5f,1.0f),NULL));
	//白箱子
	baixiangzhi = CCSprite::createWithSpriteFrameName("raffle_bai100.png");
	baixiangzhi->setPosition(ccp(320,380));
	baixiangzhi->setScale(2.0f);
	baixiangzhi->setOpacity(0);
	this->addChild(baixiangzhi);
	baixiangzhi->runAction(CCSequence::create(CCFadeIn::create(0.5f),
		CCCallFunc::create(this,callfunc_selector(RaffleTenLayer::show_xiangzhi)),NULL));

}

void RaffleTenLayer::show_xiangzhi()
{
	this->removeChild(raffle_he_flash);
	this->removeChild(baixiangzhi);
	//光白
	raffle_guangbai = CCSprite::createWithSpriteFrameName("raffle_guangbai00.png");
	raffle_guangbai->setPosition(ccp(320,380));
	raffle_guangbai->setOpacity(0);
	this->addChild(raffle_guangbai);
	raffle_guangbai->runAction(CCSpawn::create(CCFadeIn::create(1.0f),CCScaleTo::create(1.0f,10.0f),NULL));
	raffle_guangbai->runAction(CCSequence::create(CCDelayTime::create(1.0f),
		CCCallFunc::create(this,callfunc_selector(RaffleTenLayer::remove_xiangzhiandguang)),NULL));
	//箱子底部
	xiangzhi_bottom = CCSprite::createWithSpriteFrameName("raffle_xiangqian2.png");
	xiangzhi_bottom->setPosition(ccp(320,340));
	xiangzhi_bottom->setOpacity(0);
	this->addChild(xiangzhi_bottom);
	xiangzhi_bottom->runAction(CCFadeIn::create(0.5f));
	//箱子顶部
	xiangzhi_top = CCSprite::createWithSpriteFrameName("raffle_xianggai2.png");
	xiangzhi_top->setPosition(ccp(320,440));
	xiangzhi_top->setOpacity(0);
	this->addChild(xiangzhi_top);
	xiangzhi_top->runAction(CCSequence::create(CCFadeIn::create(0.5f),CCMoveBy::create(0.3f,ccp(0,30)),NULL));
}

void RaffleTenLayer::remove_xiangzhiandguang()
{
	this->removeChild(raffle_guangbai);
	this->removeChild(xiangzhi_top);
	//新的箱子顶部
	xiangzhi_top_new = CCSprite::createWithSpriteFrameName("raffle_xianggai.png");
	xiangzhi_top_new->setPosition(ccp(380,430));
	this->addChild(xiangzhi_top_new);
	//箱子的背
	CCSprite* xiangzhi_xiangbei = CCSprite::createWithSpriteFrameName("raffle_xiangbei.png");
	xiangzhi_xiangbei->setPosition(ccp(320,370));
	this->addChild(xiangzhi_xiangbei);
	//卡牌的光
	CCSprite* card_guang = CCSprite::createWithSpriteFrameName("raffle_guangbai00.png");
	card_guang->setPosition(ccp(320,400));
	card_guang->setScale(2.0f);
	card_guang->setOpacity(0);
	this->addChild(card_guang);
	card_guang->runAction(CCRepeatForever::create(CCRotateBy::create(0.5f,90)));
	card_guang->runAction(CCFadeIn::create(2.0f));

	this->runAction(CCSequence::create(CCDelayTime::create(0.3f),
		CCCallFunc::create(this,callfunc_selector(RaffleTenLayer::show_card)),NULL));
}


void RaffleTenLayer::show_card()
{
	this->schedule(schedule_selector(RaffleTenLayer::show_box_card),0.2f);
}
//显示关闭菜单
void RaffleTenLayer::show_menu()
{
	CCSprite* button_close_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* button_close_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* button_close_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	CCMenuItemSprite* button_close_item = CCMenuItemSprite::create(button_close_nor,
		button_close_sel,
		button_close_disable,
		this,
		menu_selector(RaffleTenLayer::menu_comfirm_callback));
	CCSprite* text_close = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_close.png"));
	text_close->setPosition(ccp(button_close_nor->getContentSize().width/2,button_close_nor->getContentSize().height/2));
	button_close_item->addChild(text_close);
	CCMenu* menu_close = CCMenu::create(button_close_item,NULL);
	menu_close->setPosition(ccp(320,150));
	this->addChild(menu_close);
}

void RaffleTenLayer::show_box_card(float)
{
	if(m_cardth < 10)
	{
		CCSprite* box_card = CCSprite::createWithSpriteFrameName("raffle_box_card.png");
		box_card->setScale(0.3f);
		box_card->setTag(m_cardth);
		box_card->setPosition(ccp(320,400));
		this->addChild(box_card);
		box_card->runAction(CCSpawn::create(CCMoveTo::create(0.2f,ccp(m_posx[m_cardth],m_posy[m_cardth])),
			CCScaleTo::create(0.2f,1.0f),NULL));
		m_cardth++;
	}
	else
	{
		this->unschedule(schedule_selector(RaffleTenLayer::show_box_card));
		this->schedule(schedule_selector(RaffleTenLayer::show_box_card_front),0.2f);
		m_cardth = 0;
	}
}

void RaffleTenLayer::show_box_card_front(float)
{
	if(m_cardth < 10)
	{
		this->getChildByTag(m_cardth)->runAction(CCSequence::create(CCFadeOut::create(0.3f),
			CCCallFuncN::create(this,callfuncN_selector(RaffleTenLayer::remove_box_card)),NULL));
		CCNode* card = CCNode::create();
		card->setPosition(ccp(m_posx[m_cardth],m_posy[m_cardth]));
		this->addChild(card);
		CCSprite* card_frame = CCSprite::createWithSpriteFrameName("littlecard_frame_class4_elite.png");
		card_frame->setOpacity(0);
		card->addChild(card_frame);
		card_frame->runAction(CCFadeIn::create(0.5f));

		CCString* str = CCString::createWithFormat("eatedcard%d",pcards[m_cardth]);
		CCSprite* card_content = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString));
		card_content->setOpacity(0);
		card->addChild(card_content);
		card_content->runAction(CCFadeIn::create(0.5f));
		m_cardth++;
	}
	else
	{
		m_cardth = 0;
		this->unschedule(schedule_selector(RaffleTenLayer::show_box_card_front));
		this->runAction(CCSequence::create(CCDelayTime::create(1.0f),
			CCCallFunc::create(this,callfunc_selector(RaffleTenLayer::show_menu)),NULL));
	}
}

void RaffleTenLayer::remove_box_card(CCNode* pSender)
{
	pSender->removeFromParent();
}


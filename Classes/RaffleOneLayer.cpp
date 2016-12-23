#include "RaffleOneLayer.h"
#include "AppMacros.h"
#include "AppStringFile.h"

int RaffleOneLayer::rand_cardindex = 0;

CCScene* RaffleOneLayer::scene(int index)
{
	rand_cardindex = index;
	CCScene* scene = CCScene::create();
	RaffleOneLayer* layer = RaffleOneLayer::create();
	scene->addChild(layer);
	return scene;
}

bool RaffleOneLayer::init()
{
	if(!CCLayer::init())return false;
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_choujiang.mp3");
	initBK();
	return true;
}

void RaffleOneLayer::initBK()
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
		CCCallFunc::create(this,callfunc_selector(RaffleOneLayer::show_chuizhiguang)),NULL));
}

void RaffleOneLayer::menu_comfirm_callback(CCObject*)
{
	SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/main.mp3",true);
	CCDirector::sharedDirector()->popScene();
}

void RaffleOneLayer::show_chuizhiguang()
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
		CCCallFunc::create(this,callfunc_selector(RaffleOneLayer::chuizhiguang_done)),NULL));
}

void RaffleOneLayer::chuizhiguang_done()
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
		CCCallFunc::create(this,callfunc_selector(RaffleOneLayer::show_xiangzhi)),NULL));

}

void RaffleOneLayer::show_xiangzhi()
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
		CCCallFunc::create(this,callfunc_selector(RaffleOneLayer::remove_xiangzhiandguang)),NULL));
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

void RaffleOneLayer::remove_xiangzhiandguang()
{
	this->removeChild(raffle_guangbai);
	this->removeChild(xiangzhi_bottom);
	this->removeChild(xiangzhi_top);
	this->removeChild(raffle_daguang_flash);

	white_layer = CCLayerColor::create(ccc4(255,255,255,30));
	this->addChild(white_layer);
	white_layer->runAction(CCSequence::create(CCFadeOut::create(0.8f),
		CCCallFunc::create(this,callfunc_selector(RaffleOneLayer::remove_whitelayer)),NULL));

	this->runAction(CCSequence::create(CCDelayTime::create(0.3f),
		CCCallFunc::create(this,callfunc_selector(RaffleOneLayer::show_card)),NULL));
}

void RaffleOneLayer::remove_whitelayer()
{
	this->removeChild(white_layer);
}

void RaffleOneLayer::show_card()
{
	CCSprite* card_guang = CCSprite::createWithSpriteFrameName("raffle_guangbai00.png");
	card_guang->setPosition(ccp(320,650));
	card_guang->setOpacity(0);
	this->addChild(card_guang);
	card_guang->runAction(CCRepeatForever::create(CCRotateBy::create(0.5f,90)));
	card_guang->runAction(CCFadeIn::create(2.0f));
	//添加卡牌
	CCNode* card = CCNode::create();
	card->setPosition(ccp(320,650));
	this->addChild(card);
	CCSprite* card_frame = CCSprite::createWithSpriteFrameName("bigcard_frame_class4_elite.png");
	card_frame->setOpacity(0);
	card->addChild(card_frame);
	card_frame->runAction(CCFadeIn::create(2.0f));

	CCString* str = CCString::createWithFormat("eatedcard%d",rand_cardindex);
	CCSprite* card_content = CCSprite::create(AppStringFile::sharedAppStringFile()->getStringForKey(str->m_sString));
	card_content->setScaleX(1.9f);
	card_content->setScaleY(2.1f);
	card_content->setPositionY(20);
	card_content->setOpacity(0);
	card->addChild(card_content);
	card_content->runAction(CCFadeIn::create(2.0f));

	CCSprite* card_occupation_base = CCSprite::createWithSpriteFrameName("icon_occupation_base_elite.png");
	card->addChild(card_occupation_base);
	card_occupation_base->setOpacity(0);
	card_occupation_base->runAction(CCFadeIn::create(2.0f));

	CCSprite* card_occupation = CCSprite::createWithSpriteFrameName("icon_occupation_shaman_button.png");
	card_occupation->setScale(2.0f);
	card_occupation->setOpacity(0);
	card_occupation->setPosition(ccp(61,-73));
	card->addChild(card_occupation);
	card_occupation->runAction(CCSequence::create(CCFadeIn::create(2.0f),
		CCCallFunc::create(this,callfunc_selector(RaffleOneLayer::show_menu)),NULL));
}
//显示关闭菜单
void RaffleOneLayer::show_menu()
{
	CCSprite* button_close_nor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_0.png"));
	CCSprite* button_close_sel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_1.png"));
	CCSprite* button_close_disable = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_little_2.png"));
	CCMenuItemSprite* button_close_item = CCMenuItemSprite::create(button_close_nor,
		button_close_sel,
		button_close_disable,
		this,
		menu_selector(RaffleOneLayer::menu_comfirm_callback));
	CCSprite* text_close = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("text_close.png"));
	text_close->setPosition(ccp(button_close_nor->getContentSize().width/2,button_close_nor->getContentSize().height/2));
	button_close_item->addChild(text_close);
	CCMenu* menu_close = CCMenu::create(button_close_item,NULL);
	menu_close->setPosition(ccp(320,150));
	this->addChild(menu_close);
}


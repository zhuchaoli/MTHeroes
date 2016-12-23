#include "StoryLayer.h"
#include "AppMacros.h"
#include "MainUIScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool StoryLayer::init()
{
	if(!CCLayer::init())return false;
	this->xingxing = NULL;
	//加载开场动画的背景音乐
	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("mp3/login.mp3");
	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mp3/login.mp3");
	//跳过动画场景的菜单
	CCSprite * passStoryNor = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_textbase.png"));
	CCSprite * passStorySel = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_textbase.png"));
	CCMenuItemSprite* passStoryItem = CCMenuItemSprite::create(passStoryNor,
															   passStorySel,
															   this,
															   menu_selector(StoryLayer::passStory));
	CCMenu * passStoryMenu = CCMenu::create(passStoryItem,NULL);
	passStoryItem->setPosition(ccp(680,900));
	passStoryMenu->setPosition(ccp(0,0));
	passStoryItem->setScale(2.0f);
	this->addChild(passStoryMenu,3);//zOrder设置为3
	//在菜单上放文字
	CCSprite * passStoryText = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_next.png"));
	passStoryText->setPosition(ccp(550,900));
	this->addChild(passStoryText,4);//zOrder设置为4
	//开始场景1
	beginScene1();
	//调试直接进入第三幕
	//beginScene3();
	return true;
}

void StoryLayer::update(float)
{
	if(this->xingxing != NULL)
	{
		this->background1->setPositionX(this->background1->getPositionX()-0.1);
		this->xingxing->setPositionX(this->xingxing->getPositionX()-0.1);
	}
}

//跳过动画场景
void StoryLayer::passStory(CCObject *)
{
	CCDirector::sharedDirector()->replaceScene(MainUIScene::create());
}

void StoryLayer::beginScene1()
{
	//加载上层背景
	this->background1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_background1.jpg"));
	this->background1->setAnchorPoint(ccp(0,1));
	this->background1->setPosition(ccp(0,visibleSize.height));
	this->addChild(this->background1);
	this->background1->setOpacity(0);//设置全透明 配合动作fadein
	this->background1->setScale(2.0f);//先放大两倍
	CCFadeIn * fadeIn = CCFadeIn::create(5.0f);
	CCScaleBy * scaleby = CCScaleBy::create(1.0f,0.8f);
	CCSpawn * spawn = CCSpawn::create(fadeIn,scaleby,NULL);//两个动作同时执行
	this->background1->runAction(spawn);
	//加载字幕背景
	CCSprite * zimuBackground = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_zimuBackground.png"));
	zimuBackground->setScaleX(8.0f);
	zimuBackground->setScaleY(2.0f);
	zimuBackground->setAnchorPoint(ccp(0.5,0));
	zimuBackground->setPosition(ccp(visibleSize.width/2,0));
	this->addChild(zimuBackground,1);//zOrder=1
	//字幕
	scheduleOnce(schedule_selector(StoryLayer::showText1),2.0f);
	scheduleOnce(schedule_selector(StoryLayer::showText2),4.5f);
	//星星闪烁 3秒之后 执行xingxingFlash函数
	CCDelayTime * delayTime = CCDelayTime::create(3.0f);
	CCCallFunc * callFunc = CCCallFunc::create(this,callfunc_selector(StoryLayer::xingxingFlash));
	CCSequence * seq = CCSequence::create(delayTime,callFunc,NULL);
	this->runAction(seq);

	//切换场景2
	scheduleOnce(schedule_selector(StoryLayer::endScene1),8.0f);
	scheduleUpdate();
}

void StoryLayer::endScene1(float)
{
	CCFadeOut* fadeout = CCFadeOut::create(1.0f);
	background1->runAction(fadeout);
	CCFadeOut* fadeout2 = CCFadeOut::create(1.0f);
	xingxing->stopAllActions();
	xingxing->runAction(fadeout2);
	//延迟1秒进入第二幕
	CCDelayTime* delaytime = CCDelayTime::create(1.0f);
	CCCallFunc* callfunc = CCCallFunc::create(this,callfunc_selector(StoryLayer::beginScene2));
	CCSequence* seq = CCSequence::create(delaytime,callfunc,NULL);
	this->runAction(seq);
}

void StoryLayer::beginScene2()
{
	this->unscheduleAllSelectors();//取消所有的定时
	this->removeChild(background1,true);
	this->removeChild(xingxing,true);
	//加载第二幕
	background2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_02tu2.jpg"));
	background2->setScale(1.8f);
	background2->setAnchorPoint(ccp(0.5,1));
	background2->setPosition(ccp(visibleSize.width/2,visibleSize.height+100));
	this->addChild(background2);
	//火堆
	huodui = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_huodui.png"));
	huodui->setPosition(ccp(120,380));
	this->addChild(huodui);
	//mt
	play_mt = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_mtt.png"));
	play_mt->setPosition(ccp(415,325));
	this->addChild(play_mt);
	//得得
	play_dede = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_dede.png"));
	play_dede->setPosition(ccp(310,315));
	this->addChild(play_dede);
	//傻馒
	play_shaman = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_shaman.png"));
	play_shaman->setPosition(ccp(205,305));
	this->addChild(play_shaman);

	scheduleOnce(schedule_selector(StoryLayer::showText3),1.0f);
	scheduleOnce(schedule_selector(StoryLayer::showText4),3.5f);
	scheduleOnce(schedule_selector(StoryLayer::showText5),6.0f);
	scheduleOnce(schedule_selector(StoryLayer::showText6),8.5f);
	scheduleOnce(schedule_selector(StoryLayer::showText7),11.0f);
	//结束第二幕
	scheduleOnce(schedule_selector(StoryLayer::endScene2),13.5f);
}

void StoryLayer::endScene2(float)
{
	CCFadeOut* fadeout1 = CCFadeOut::create(1.0f);
	background2->runAction(fadeout1);
	CCFadeOut* fadeout2 = CCFadeOut::create(1.0f);
	huodui->runAction(fadeout2);
	CCFadeOut* fadeout3 = CCFadeOut::create(1.0f);
	play_shaman->runAction(fadeout3);
	CCFadeOut* fadeout4 = CCFadeOut::create(1.0f);
	play_mt->runAction(fadeout4);
	CCFadeOut* fadeout5 = CCFadeOut::create(1.0f);
	play_dede->runAction(fadeout5);
	//延迟1秒进入第三幕
	CCDelayTime* delaytime = CCDelayTime::create(1.0f);
	CCCallFunc* callfunc = CCCallFunc::create(this,callfunc_selector(StoryLayer::beginScene3));
	CCSequence* seq = CCSequence::create(delaytime,callfunc,NULL);
	this->runAction(seq);
}

void StoryLayer::beginScene3()
{
	this->unscheduleAllSelectors();//取消所有的定时
	this->removeChild(background2,true);
	this->removeChild(huodui,true);
	this->removeChild(play_dede,true);
	this->removeChild(play_mt,true);
	this->removeChild(play_shaman,true);
	//加载第三幕
	background3 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_03tu1.jpg"));//play_03tu1.jpg
	background3->setScale(1.8f);
	background3->setAnchorPoint(ccp(0.5,1));
	background3->setOpacity(0);
	background3->setPosition(ccp(visibleSize.width/2,visibleSize.height+120));
	this->addChild(background3);
	CCFadeIn* bfadein = CCFadeIn::create(0.3f);
	background3->runAction(bfadein);

	//加载光线
	guangxian = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_guangxian.png"));
	guangxian->setAnchorPoint(ccp(0.5,1));
	guangxian->setPosition(ccp(visibleSize.width/2,visibleSize.height));
	guangxian->setScale(3.0f);
	this->addChild(guangxian);
	CCFadeIn* fadein = CCFadeIn::create(1.5f);
	CCFadeOut* fadeout = CCFadeOut::create(1.5f);
	CCSequence* seq = CCSequence::create(fadein,fadeout,NULL);
	guangxian->runAction(CCRepeatForever::create(seq));
	//石头人
	shiren1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_shiren.png"));
	shiren2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_shiren.png"));
	shiren3 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_shiren.png"));
	shiren1->setScale(0.6f);
	shiren2->setScale(2.0f);
	shiren3->setScale(1.0f);
	shiren1->setPosition(ccp(50,340));
	shiren2->setPosition(ccp(250,320));
	shiren3->setPosition(ccp(580,380));
	this->addChild(shiren1);
	this->addChild(shiren2);
	this->addChild(shiren3);
	shiren1->setOpacity(0);
	shiren2->setOpacity(0);
	shiren3->setOpacity(0);
	CCFadeIn* fadein1 = CCFadeIn::create(0.3f);
	CCFadeIn* fadein2 = CCFadeIn::create(0.5f);
	CCFadeIn* fadein3 = CCFadeIn::create(0.5f);
	CCDelayTime* dt1 = CCDelayTime::create(3.5f);
	CCDelayTime* dt2 = CCDelayTime::create(3.5f);
	CCDelayTime* dt3 = CCDelayTime::create(3.5f);
	CCSequence* seq1 = CCSequence::create(dt1,fadein1,NULL);
	CCSequence* seq2 = CCSequence::create(dt2,fadein2,NULL);
	CCSequence* seq3 = CCSequence::create(dt3,fadein3,NULL);
	shiren1->runAction(seq1);
	shiren2->runAction(seq2);
	shiren3->runAction(seq3);
	//天火
	tianhuo1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_1.png"));
	tianhuo2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_bao2.png"));
	tianhuo31 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_bao3.png"));
	tianhuo32 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_bao3.png"));
	tianhuo33 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_bao3.png"));
	tianhuo1->setPosition(ccp(visibleSize.width/2+50,visibleSize.height-20));
	tianhuo2->setPosition(ccp(visibleSize.width/2-30,visibleSize.height-20));
	tianhuo31->setPosition(ccp(visibleSize.width/2-50,visibleSize.height/2+100));
	tianhuo32->setPosition(ccp(visibleSize.width-50,visibleSize.height/2+100));
	tianhuo33->setPosition(ccp(visibleSize.width-50,visibleSize.height/2));
	this->addChild(tianhuo1);
	this->addChild(tianhuo2);
	this->addChild(tianhuo31);
	this->addChild(tianhuo32);
	this->addChild(tianhuo33);
	CCMoveBy* moveby1 = CCMoveBy::create(1.0f,ccp(-80,-80));
	CCMoveBy* moveby2 = CCMoveBy::create(1.0f,ccp(-100,-100));
	CCMoveBy* moveby3 = CCMoveBy::create(1.0f,ccp(-80,-80));
	CCMoveBy* moveby4 = CCMoveBy::create(1.0f,ccp(-80,-80));
	CCMoveBy* moveby5 = CCMoveBy::create(1.0f,ccp(-80,-80));
	tianhuo1->runAction(moveby1);
	tianhuo2->runAction(moveby2);
	tianhuo31->runAction(moveby3);
	tianhuo32->runAction(moveby4);
	tianhuo33->runAction(moveby5);
	scheduleOnce(schedule_selector(StoryLayer::showText8),1.0f);
	scheduleOnce(schedule_selector(StoryLayer::showText9),3.5f);
	
	scheduleOnce(schedule_selector(StoryLayer::endScene3),6.0f);
}

void StoryLayer::endScene3(float)
{
	CCFadeOut* fadeout1 = CCFadeOut::create(1.0f);
	background3->runAction(fadeout1);
	CCFadeOut* fadeout2 = CCFadeOut::create(1.0f);
	guangxian->stopAllActions();
	guangxian->runAction(fadeout2);
	CCFadeOut* fadeout3 = CCFadeOut::create(1.0f);
	shiren1->runAction(fadeout3);
	CCFadeOut* fadeout4 = CCFadeOut::create(1.0f);
	shiren2->runAction(fadeout4);
	CCFadeOut* fadeout5 = CCFadeOut::create(1.0f);
	shiren3->runAction(fadeout5);
	CCFadeOut* fadeout6 = CCFadeOut::create(1.0f);
	tianhuo1->runAction(fadeout6);
	CCFadeOut* fadeout7 = CCFadeOut::create(1.0f);
	tianhuo2->runAction(fadeout7);
	CCFadeOut* fadeout8 = CCFadeOut::create(1.0f);
	tianhuo31->runAction(fadeout8);
	CCFadeOut* fadeout9 = CCFadeOut::create(1.0f);
	tianhuo32->runAction(fadeout9);
	CCFadeOut* fadeout10 = CCFadeOut::create(1.0f);
	tianhuo33->runAction(fadeout10);
	//延迟1秒进入第四幕
	CCDelayTime* delaytime = CCDelayTime::create(1.0f);
	CCCallFunc* callfunc = CCCallFunc::create(this,callfunc_selector(StoryLayer::beginScene4));
	CCSequence* seq = CCSequence::create(delaytime,callfunc,NULL);
	this->runAction(seq);
}

void StoryLayer::beginScene4()
{
	this->unscheduleAllSelectors();//取消所有的定时
	this->removeChild(background3,true);
	this->removeChild(guangxian,true);
	this->removeChild(shiren1,true);
	this->removeChild(shiren2,true);
	this->removeChild(shiren3,true);
	this->removeChild(tianhuo1,true);
	this->removeChild(tianhuo2,true);
	this->removeChild(tianhuo31,true);
	this->removeChild(tianhuo32,true);
	this->removeChild(tianhuo33,true);

	//加载第四幕
	background2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_02tu2.jpg"));
	background2->setScale(1.8f);
	background2->setAnchorPoint(ccp(0.5,1));
	background2->setPosition(ccp(visibleSize.width/2,visibleSize.height+120));
	this->addChild(background2);
	//火堆
	huodui = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_huodui.png"));
	huodui->setPosition(ccp(120,380));
	this->addChild(huodui);
	//mt
	play_mt = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_mtt.png"));
	play_mt->setPosition(ccp(415,325));
	this->addChild(play_mt);
	//得得
	play_dede = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_dede.png"));
	play_dede->setPosition(ccp(310,315));
	this->addChild(play_dede);
	//傻馒
	play_shaman = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_shaman.png"));
	play_shaman->setPosition(ccp(205,305));
	this->addChild(play_shaman);

	scheduleOnce(schedule_selector(StoryLayer::showText10),1.0f);
	scheduleOnce(schedule_selector(StoryLayer::showText11),3.5f);
	
	//结束第四幕
	scheduleOnce(schedule_selector(StoryLayer::endScene4),5.0f);
}

void StoryLayer::endScene4(float)
{
	CCFadeOut* fadeout1 = CCFadeOut::create(1.0f);
	background2->runAction(fadeout1);
	CCFadeOut* fadeout2 = CCFadeOut::create(1.0f);
	huodui->runAction(fadeout2);
	CCFadeOut* fadeout3 = CCFadeOut::create(1.0f);
	play_shaman->runAction(fadeout3);
	CCFadeOut* fadeout4 = CCFadeOut::create(1.0f);
	play_mt->runAction(fadeout4);
	CCFadeOut* fadeout5 = CCFadeOut::create(1.0f);
	play_dede->runAction(fadeout5);
	//延迟1秒进入第五幕
	CCDelayTime* delaytime = CCDelayTime::create(1.0f);
	CCCallFunc* callfunc = CCCallFunc::create(this,callfunc_selector(StoryLayer::beginScene5));
	CCSequence* seq = CCSequence::create(delaytime,callfunc,NULL);
	this->runAction(seq);
}

void StoryLayer::beginScene5()
{
	this->unscheduleAllSelectors();//取消所有的定时
	//this->removeAllChildren();
	this->removeChild(background2,true);
	this->removeChild(huodui,true);
	this->removeChild(play_dede,true);
	this->removeChild(play_mt,true);
	this->removeChild(play_shaman,true);
	scheduleOnce(schedule_selector(StoryLayer::showText12),1.0f);
	scheduleOnce(schedule_selector(StoryLayer::showText13),3.5f);
	scheduleOnce(schedule_selector(StoryLayer::showText14),6.0f);
	//结束第五幕
	scheduleOnce(schedule_selector(StoryLayer::endScene5),8.5f);
}

void StoryLayer::endScene5(float)
{
	/*CCFadeOut* fadeout1 = CCFadeOut::create(1.0f);
	text[11]->runAction(fadeout1);
	CCFadeOut* fadeout2 = CCFadeOut::create(1.0f);
	text[12]->runAction(fadeout2);
	CCFadeOut* fadeout3 = CCFadeOut::create(1.0f);
	text[13]->runAction(fadeout3);*/
	this->removeAllChildren();
	CCDirector::sharedDirector()->replaceScene(MainUIScene::create());
}

void StoryLayer::xingxingFlash()
{
	this->xingxing = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("play_xing.png"));
	this->xingxing->setPosition(ccp(384,742));
	this->addChild(this->xingxing);
	CCFadeIn* fadein = CCFadeIn::create(0.8f);
	CCFadeOut* fadeout = CCFadeOut::create(0.8f);
	CCSequence * seq = CCSequence::create(fadein,fadeout,NULL);
	this->xingxing->runAction(CCRepeatForever::create(seq));
}

void StoryLayer::showText1(float)
{
	showText(text[0],"play_1tuzi1.png");
}

void StoryLayer::showText2(float)
{
	showText(text[1],"play_1tuzi2.png");
}

void StoryLayer::showText3(float)
{
	showText(text[2],"play_2zi1z.png");
	shakeHead(play_shaman);
	showTextBox(text3box,"play_shakuang01.png",ccp(245,380));
}
void StoryLayer::showText4(float)
{
	showText(text[3],"play_2zi2z.png");
	shakeHead(play_mt);
	showTextBox(text3box,"play_mtkuang01.png",ccp(380,380));
}
void StoryLayer::showText5(float)
{
	showText(text[4],"play_2zi3z.png");
	shakeHead(play_shaman);
	showTextBox(text3box,"play_shakuang02.png",ccp(245,380));
}
void StoryLayer::showText6(float)
{
	showText(text[5],"play_2zi4z.png");
	shakeHead(play_mt);
	showTextBox(text3box,"play_mtkuang02.png",ccp(380,380));

}
void StoryLayer::showText7(float)
{
	showText(text[6],"play_2zi5z.png");
	shakeHead(play_dede);
	showTextBox(text3box,"play_dekuang01.png",ccp(270,380));
}

void StoryLayer::showText8(float)
{
	showText(text[7],"play_03zi1.png");
}

void StoryLayer::showText9(float)
{
	showText(text[8],"play_03zi2.png");
}

void StoryLayer::showText10(float)
{
	showText(text[9],"play_04zi1.png");
}

void StoryLayer::showText11(float)
{
	showText(text[10],"play_04zi2.png");
}

void StoryLayer::showText12(float)
{
	showText(text[11],"play_05zi1.png",1.0f,ccp(50,600),ccp(0,80),false);
}

void StoryLayer::showText13(float)
{
	showText(text[12],"play_05zi2.png",1.8f,ccp(50,530),ccp(0,80),false);
}

void StoryLayer::showText14(float)
{
	showText(text[13],"play_05zi3.png",0,ccp(50,420),ccp(0,80),false);
}

void StoryLayer::showText(CCSprite* &spr,const char * name,float dt/*=1.0f*/,CCPoint initpos /*= ccp(20,80)*/,CCPoint movepos /*= ccp(0,80)*/,bool isDisappear /*= true*/)
{
	spr = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
	spr->setAnchorPoint(ccp(0,1));
	spr->setScale(1.2f);
	spr->setPosition(initpos);
	this->addChild(spr,2);
	//字幕动画
	CCMoveBy *moveby = CCMoveBy::create(1.0f,movepos);
	if(isDisappear)//如果需要移除
	{
		CCDelayTime* delaytime = CCDelayTime::create(dt);
		CCFadeOut* fadeout = CCFadeOut::create(1.0f);
		CCCallFuncND * callfuncnd = CCCallFuncND::create(this,callfuncND_selector(StoryLayer::removeSprite),spr);
		CCSequence* seq = CCSequence::create(moveby,delaytime,fadeout,callfuncnd,NULL);
		spr->runAction(seq);
	}
	else
	{
		spr->runAction(moveby);
	}
}
//将字幕从场景中移除
void StoryLayer::removeSprite(CCNode* node,void* data)
{
	this->removeChild((CCSprite*)data,true);
}

void StoryLayer::shakeHead(CCSprite* &spr)
{
	CCRotateTo* to1 = CCRotateTo::create(0.5f,5.0f,0);
	CCRotateTo* to2 = CCRotateTo::create(0.5f,-5.0f,0);
	CCRotateTo* to3 = CCRotateTo::create(0.5f,0,0);
	CCSequence* seq = CCSequence::create(to1,to2,to3,NULL);
	spr->runAction(seq);
}

void StoryLayer::showTextBox(CCSprite* &spr,const char * name,CCPoint inipos)
{
	spr = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
	spr->setScale(0.5f);
	spr->setPosition(inipos);
	this->addChild(spr,2);

	CCScaleTo* scaleto = CCScaleTo::create(1.0f,1.0f);
	CCDelayTime* delaytime = CCDelayTime::create(1.5f);;
	CCFadeOut* fadeout = CCFadeOut::create(1.0f);
	CCCallFuncND* callfuncnd = CCCallFuncND::create(this,callfuncND_selector(StoryLayer::removeSprite),spr);
	CCSequence* seq = CCSequence::create(scaleto,delaytime,fadeout,NULL);
	spr->runAction(seq);
}


#include "MainTopUITouchLayer.h"
#include "AppStringFile.h"
#include "AppMacros.h"
#include "Hero.h"
#include "ValueConvert.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool MainTopUITouchLayer::init()
{
	if(!CCLayer::init())return false;
	setContentSize(CCSizeMake(640,240));
	setTouchEnabled(true);//��������
	return true;
}

void MainTopUITouchLayer::registerWithTouchDispatcher()
{
	CCDirector* pdirector = CCDirector::sharedDirector();
	//���ô������ն�������ȼ� ���һ����ɴ��� ���ȼ��͵Ķ����޷����յ�����
	pdirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool MainTopUITouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pt = pTouch->getLocationInView();//��ȡUI����ϵ������ ԭ�������Ͻ�
	if(pt.y <= 130 && pt.y >= 0)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("mp3/sound_select.mp3");
		InitSysInfo();
		return true;
	}
	return false;
}

void MainTopUITouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	this->unscheduleAllSelectors();
	this->removeChild(sysInfo);
}

void MainTopUITouchLayer::InitSysInfo()
{
	sysInfo = CCNode::create();
	//���
	CCSprite* tipsbase = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tipsbase.png"));
	tipsbase->setScaleY(1.5f);
	tipsbase->setPosition(ccp(320,680));
	sysInfo->addChild(tipsbase);
	//���� Ӧ�ô�Ӣ�۵�������ȥȡ�� 
	CCString * str = CCString::create("");
	str->initWithFormat("%s rank_%d",AppStringFile::sharedAppStringFile()->getStringForKey("currank_text"),Hero::sharedHero()->getRank());
	CCLabelTTF* sys_rank = CCLabelTTF::create(str->m_sString.c_str(),"Arial",20);
	sys_rank->setPosition(ccp(320,750));
	sysInfo->addChild(sys_rank);
	//�ȼ�
	str->initWithFormat("%s %d",AppStringFile::sharedAppStringFile()->getStringForKey("curlevel_text"),Hero::sharedHero()->getLevel_());
	CCLabelTTF* sys_level = CCLabelTTF::create(str->m_sString.c_str(),"Arial",20);
	sys_level->setPosition(ccp(320,722));
	sysInfo->addChild(sys_level);
	//����ֵ
	str->initWithFormat("%s %d",AppStringFile::sharedAppStringFile()->getStringForKey("curExp_text"),Hero::sharedHero()->getExp());
	CCLabelTTF* sys_exp = CCLabelTTF::create(str->m_sString.c_str(),"Arial",20);
	sys_exp->setPosition(ccp(320,694));
	sysInfo->addChild(sys_exp);
	//����
	str->initWithFormat("%s %d",AppStringFile::sharedAppStringFile()->getStringForKey("curstrength_text"),Hero::sharedHero()->getStrength());
	CCLabelTTF* sys_charm = CCLabelTTF::create(str->m_sString.c_str(),"Arial",20);
	sys_charm->setPosition(ccp(320,666));
	sysInfo->addChild(sys_charm);
	//��������ľ���ֵ
	str->initWithFormat("%s %d",AppStringFile::sharedAppStringFile()->getStringForKey("curlevelupneedexp_text"),Hero::sharedHero()->getCurLevelMaxExp()-Hero::sharedHero()->getExp());
	CCLabelTTF* sysinfo_needexp = CCLabelTTF::create(str->m_sString.c_str(),"Arial",20);
	sysinfo_needexp->setPosition(ccp(320,638));
	sysInfo->addChild(sysinfo_needexp);
	//ϵͳʱ��
	CCLabelTTF* sysinfo_time = CCLabelTTF::create(getTime().c_str(),"Arial",20);
	sysinfo_time->setTag(555);
	sysinfo_time->setPosition(ccp(320,610));
	sysInfo->addChild(sysinfo_time);

	this->addChild(sysInfo);
	schedule(schedule_selector(MainTopUITouchLayer::updateTime),1.0f);
}

string MainTopUITouchLayer::getTime()
{
	struct tm *systime;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	time_t t;
	time(&t);
	systime = localtime(&t);
#else
	struct cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now,NULL);
	systime = localtime(&now.tv_sec);
#endif
	int hour = systime->tm_hour;
	int min = systime->tm_min;
	int sec = systime->tm_sec;
	CCString* str = CCString::create("");
	str->initWithFormat("%02d:%02d:%02d",hour,min,sec);
	return str->m_sString;
}

void MainTopUITouchLayer::updateTime(float)
{
	((CCLabelTTF*)(sysInfo->getChildByTag(555)))->setString(getTime().c_str());
}


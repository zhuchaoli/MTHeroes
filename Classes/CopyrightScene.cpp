#include "CopyrightScene.h"
#include "Hero.h"
#include "Archives.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool CopyrightScene::init()
{
	if(!CCScene::init())return false;
	LoadPicResoureToCache();
	LoadBackgroundMisic();
	Archives::sharedArchives();//加载存档
	this->copyrightLayer = CopyrightLayer::create();
	this->addChild(this->copyrightLayer);
	return true;
}

//一次性加载图片资源到缓存中
void CopyrightScene::LoadPicResoureToCache()
{
	CCSpriteFrameCache * pSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_0329_0335.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_0337_0343.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_0345_0351.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_0489_0494.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_frame_greenandblue.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_frame_purpleandyellow.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_frame_white.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/eatcard_part1.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/evolution.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/fight_star.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/fight_victroy.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/heal.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/login_animation.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/play_image.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/play_script1.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/play_script2.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/raffle.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/skill_customattack.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/skill_tenarmy.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/skill_thunde.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/skill_windhit.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/skill_zhongji.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/skille_blizzard.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_arena.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_eatcard.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_fight.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_friend.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_icon.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_list_button.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_listbutton1.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_littcard_frame.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_littlebutton.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_mainface.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_navigation.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_occupation.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_rank.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_serverlist.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/ui_text.plist");
}

void CopyrightScene::LoadBackgroundMisic()
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("mp3/startgame.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("mp3/story.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("mp3/main.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("mp3/battle_backgroundmusic1.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("mp3/battle_backgroundmusic2.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_select.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_horelevelup.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_horeselected.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/battle_battlestart.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/battle_failed.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/battle_herodead.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/battle_monsterdead.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/battle_run.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/battle_win.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_skill01.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_skill02.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_skill03.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_skill04.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_skill05.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_skill06.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_skill07.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_skill08.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_skill09.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_skill10.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("mp3/sound_choujiang.mp3");
}


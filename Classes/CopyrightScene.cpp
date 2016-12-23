#include "CopyrightScene.h"
#include "Hero.h"
#include "Archives.h"

bool CopyrightScene::init()
{
	if(!CCScene::init())return false;
	LoadPicResoureToCache();
	LoadHeroProperty();
	this->copyrightLayer = CopyrightLayer::create();
	this->addChild(this->copyrightLayer);
	return true;
}

//һ���Լ���ͼƬ��Դ��������
void CopyrightScene::LoadPicResoureToCache()
{
	CCSpriteFrameCache * pSpriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_0000_0004.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_0329_0335.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_0337_0343.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_0345_0351.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_0489_0494.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_frame_greenandblue.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_frame_purpleandyellow.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/bigcard_frame_white.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/eatcard_part1.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/equipment_part1.plist");
	pSpriteFrameCache->addSpriteFramesWithFile("ui/equipment_part2.plist");
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
//���ش浵
void CopyrightScene::LoadHeroProperty()
{
	Archives::sharedArchives();
	//��Ϸ������ɺ��ٴ浵
	//Archives::sharedArchives()->setArchives();
}

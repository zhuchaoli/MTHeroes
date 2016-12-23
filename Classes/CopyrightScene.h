#pragma once
#include "cocos2d.h"
#include "CopyrightLayer.h"
USING_NS_CC;

class CopyrightScene : public CCScene
{
public:
	CREATE_FUNC(CopyrightScene);
	bool init();
private:
	void LoadPicResoureToCache();//加载图片资源到缓存
	void LoadBackgroundMisic();//预加载音乐
private:
	CopyrightLayer * copyrightLayer;
};


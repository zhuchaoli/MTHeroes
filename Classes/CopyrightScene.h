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
	void LoadPicResoureToCache();//����ͼƬ��Դ������
	void LoadHeroProperty();//����Ӣ������
private:
	CopyrightLayer * copyrightLayer;
};


#pragma once
#include "cocos2d.h"
#include "StoryLayer.h"
USING_NS_CC;

class StoryScene : public CCScene
{
public:
	CREATE_FUNC(StoryScene);
	bool init();
private:
	StoryLayer * storyLayer;
};
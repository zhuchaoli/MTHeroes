#include "StoryScene.h"

bool StoryScene::init()
{
	if(!CCScene::init())return false;
	this->storyLayer = StoryLayer::create();
	this->addChild(this->storyLayer);
	return true;
}


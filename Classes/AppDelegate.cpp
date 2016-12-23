#include "AppDelegate.h"
#include "CopyrightScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	pEGLView->setDesignResolutionSize(640, 960,kResolutionExactFit);//��Ʒֱ��� ȥ��Ӧ��Ļ
    // turn on display FPS
    pDirector->setDisplayStats(false);//ȥ�����½ǵ���ʾ

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	//�Ӱ�Ȩ��¼����������Ϸ
    CCScene *pScene = CopyrightScene::create();
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

#pragma once
#include "cocos2d.h"
#include "vector"
#include "algorithm"
using namespace std;
USING_NS_CC;

#define SPEED_X1 0
#define SPEED_X2 1
#define SPEED_X3 2
#define FIRST    1
#define SECOND   2
#define THIRD    3

class BattleLayer:public CCLayer
{
public:
	static CCScene* scene();
	CREATE_FUNC(BattleLayer);
	bool init();
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
private:
	void initBk();
	void initContent();
	void initSkillAnimation();
	void initMonsterLifeAndAttack();//初始化怪物生命和攻击
	void initMonsterOrder();//初始化怪物的队形
	void first_hero_play(float);//第一幕英雄打
	void first_monster_play(float);//第一幕怪物打
	void second_hero_play(float);//第二幕英雄打
	void second_monster_play(float);//第二幕怪物打
	void third_hero_play(float);//第三幕英雄打
	void third_monster_play(float);//第三幕怪物打

	//英雄和怪物的技能
	void hero_0_skill(int pos,int dst);
	void hero_1_skill(int pos,int dst);
	void hero_2_skill(int pos,int dst);
	void hero_3_skill(int pos,int dst);
	void hero_4_skill(int pos,int dst);
	void monster_0_skill(int pos,int dst);
	void monster_1_skill(int pos,int dst);
	void monster_2_skill(int pos,int dst);
	void monster_3_skill(int pos,int dst);
	void monster_4_skill(int pos,int dst);
	void monster_5_skill(int pos,int dst);
	void monster_6_skill(int pos,int dst);
	void monster_7_skill(int pos,int dst);
	void monster_8_skill(int pos,int dst);
	void monster_9_skill(int pos,int dst);
	void monster_10_skill(int pos,int dst);

	void runCard();//英雄的移动
	void runBK();//背景的移动
	void adjustBK1();
	void adjustBK2();
	void runcardshake();//英雄的晃动

	void show_skill(int pos,CCNode** node,int* x,int* y,const char* skillname,const char * skill_spritename,int dst);
	void show_skill_normal(int pos,CCNode** node,int* x,int* y,int type,int dst,int* dx,int* dy);
	void remove_skill(CCNode*);
	void show_hit_skill(int pos,const char* skillname,const char * skill_spritename,int dst,int* dx,int* dy);
	void remove_hit_skill(CCNode*,void*);
	void show_hit_value(int pos,int* posattack,int dst,int* dx,int* dy);
	void remove_hit_value(CCNode*);
	void monster_die(int pos);
	void show_ghost(CCNode* ,void* pos);
	void remove_ghost(CCNode*);

	void show_goahead();//显示前进标志
	void show_allmonster(float);//显示怪物

	void showVictory();//现在战斗胜利
	void showFail();//显示战斗失败
	void showReult(float);
	void showText(float);//显示战斗
private:
	CCSprite* bk_1;
	CCSprite* bk_2;
	CCSprite* bk_3;
	CCSprite* goahead;
	CCNode* hero[5];//5个英雄
	CCNode* monster[11];//11个怪物
	int hero_life[5];
	int hero_attack[5];
	int monster_life[11];
	int monster_attack[11];
	int monster_order[11];//怪物的队形
	//英雄和怪物的坐标
	int pos_hero_x[5];
	int pos_hero_y[5];
	int pos_monster_x[11];
	int pos_monster_y[11];

	CCSprite* speed[3];//三个速度标志
	int m_curSpeed;//当前速度
	bool m_isShowGoAhead;//前进标志是否显示出来
	int m_curPlay;//当前第几波战斗

	CCNode* result;

	int curGuanQia;//当前第几关
	vector<int> hero_alive;
	vector<int> monster_alive;
	bool gongjifang;//当前攻击方   true->英雄  false->怪物
	int bkmovecount;//背景是第几次移动
	int effectId;//音效ID
};
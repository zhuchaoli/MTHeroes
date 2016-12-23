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
	void initMonsterLifeAndAttack();//��ʼ�����������͹���
	void initMonsterOrder();//��ʼ������Ķ���
	void first_hero_play(float);//��һĻӢ�۴�
	void first_monster_play(float);//��һĻ�����
	void second_hero_play(float);//�ڶ�ĻӢ�۴�
	void second_monster_play(float);//�ڶ�Ļ�����
	void third_hero_play(float);//����ĻӢ�۴�
	void third_monster_play(float);//����Ļ�����

	//Ӣ�ۺ͹���ļ���
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

	void runCard();//Ӣ�۵��ƶ�
	void runBK();//�������ƶ�
	void adjustBK1();
	void adjustBK2();
	void runcardshake();//Ӣ�۵Ļζ�

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

	void show_goahead();//��ʾǰ����־
	void show_allmonster(float);//��ʾ����

	void showVictory();//����ս��ʤ��
	void showFail();//��ʾս��ʧ��
	void showReult(float);
	void showText(float);//��ʾս��
private:
	CCSprite* bk_1;
	CCSprite* bk_2;
	CCSprite* bk_3;
	CCSprite* goahead;
	CCNode* hero[5];//5��Ӣ��
	CCNode* monster[11];//11������
	int hero_life[5];
	int hero_attack[5];
	int monster_life[11];
	int monster_attack[11];
	int monster_order[11];//����Ķ���
	//Ӣ�ۺ͹��������
	int pos_hero_x[5];
	int pos_hero_y[5];
	int pos_monster_x[11];
	int pos_monster_y[11];

	CCSprite* speed[3];//�����ٶȱ�־
	int m_curSpeed;//��ǰ�ٶ�
	bool m_isShowGoAhead;//ǰ����־�Ƿ���ʾ����
	int m_curPlay;//��ǰ�ڼ���ս��

	CCNode* result;

	int curGuanQia;//��ǰ�ڼ���
	vector<int> hero_alive;
	vector<int> monster_alive;
	bool gongjifang;//��ǰ������   true->Ӣ��  false->����
	int bkmovecount;//�����ǵڼ����ƶ�
	int effectId;//��ЧID
};
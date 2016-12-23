//������ ��һ������
#pragma once
#include "cocos2d.h"
#include <vector>
USING_NS_CC;
using namespace std;

class Hero
{
private:
	Hero();
	static Hero* m_pHero;
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if(Hero::m_pHero != NULL)delete Hero::m_pHero;
		}
	};
	static CGarbo m_garbo;//
	CC_SYNTHESIZE(string,m_name,Name_);//�������
	CC_SYNTHESIZE(int,m_level,Level_);//�ȼ�
	CC_SYNTHESIZE(int,m_diamond,Diamond);//��ʯ
	CC_SYNTHESIZE(int,m_exp,Exp);//����ֵ
	CC_SYNTHESIZE(int,m_curlevelmaxexp,CurLevelMaxExp);//��ǰ�ȼ��������ֵ
	CC_SYNTHESIZE(int,m_strength,Strength);//����
	CC_SYNTHESIZE(int,m_money,Money);//���
	CC_SYNTHESIZE(int,m_teamlv,TeamLv);//�����Ŷӵ�ʵ��
	CC_SYNTHESIZE(int,m_rank,Rank);//��λ ����
public:
	static Hero* sharedHero();
};
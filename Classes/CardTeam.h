#pragma once
#include "cocos2d.h"
#include "iostream"
using namespace std;
USING_NS_CC;

class CardTeam
{
private:
	CardTeam();
	static CardTeam* m_pCardTeam;
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if(CardTeam::m_pCardTeam != NULL)delete CardTeam::m_pCardTeam;
		}
	};
	static CGarbo m_garbo;//
public:
	static CardTeam* sharedCardTeam();

	CC_SYNTHESIZE(int,m_caption_life,caption_life);
	CC_SYNTHESIZE(int,m_caption_attack,caption_attack);
	CC_SYNTHESIZE(int,m_teammate1_life,teammate1_life);
	CC_SYNTHESIZE(int,m_teammate1_attack,teammate1_attack);
	CC_SYNTHESIZE(int,m_teammate2_life,teammate2_life);
	CC_SYNTHESIZE(int,m_teammate2_attack,teammate2_attack);
	CC_SYNTHESIZE(int,m_teammate3_life,teammate3_life);
	CC_SYNTHESIZE(int,m_teammate3_attack,teammate3_attack);
	CC_SYNTHESIZE(int,m_teammate4_life,teammate4_life);
	CC_SYNTHESIZE(int,m_teammate4_attack,teammate4_attack);
public:
	//�浵
	void  setCardTeamPor();
	//����
	void  getCardTeamPor();
	//��index��ȡ��Ա������
	int getLifeByKey(int index);
	//��index��ȡ��Ա�Ĺ���
	int getAttackByKey(int index);
	//��index���ö�Ա������
	void setLifeByKey(int index,int var);
	//��index���ö�Ա�Ĺ���
	void setAttackByKey(int index,int var);
	//��index�õ����Ƶ�����
	int getEatedCardCountByKey(int index);
	//��index���ÿ��Ƶ�����
	void setEatedCardCountByKey(int index,int var);
	int getEatedCardTotalCount();
//���������ɿ��Ƶ�����
	CC_SYNTHESIZE(int,m_eatedcard0count,eatedcard0count);
	CC_SYNTHESIZE(int,m_eatedcard1count,eatedcard1count);
	CC_SYNTHESIZE(int,m_eatedcard2count,eatedcard2count);
	CC_SYNTHESIZE(int,m_eatedcard3count,eatedcard3count);
	CC_SYNTHESIZE(int,m_eatedcard4count,eatedcard4count);
	CC_SYNTHESIZE(int,m_eatedcard5count,eatedcard5count);
};
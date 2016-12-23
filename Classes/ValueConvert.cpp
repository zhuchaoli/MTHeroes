#include "ValueConvert.h"

const char* ValueConvert::intToChar(CCString &str,const int var)
{
	str.initWithFormat("%d",var);
	return str.getCString();
}

string ValueConvert::getSelectCardKey(int index)
{
	CCString* key = CCString::create("");
	switch(index)
	{
	case 0:
		key->initWithFormat("captain_role_big");
		return key->m_sString;
	case 1:
		key->initWithFormat("teammate1_role_big");
		return key->m_sString;
	case 2:
		key->initWithFormat("teammate2_role_big");
		return key->m_sString;
	case 3:
		key->initWithFormat("teammate3_role_big");
		return key->m_sString;
	case 4:
		key->initWithFormat("teammate4_role_big");
		return key->m_sString;
	}
}


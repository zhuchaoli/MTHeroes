#pragma once
#include "cocos2d.h"
#include <iostream>
using namespace std;
USING_NS_CC;

class ValueConvert
{
public:
	static const char* intToChar(CCString &str,const int var);
	static string getSelectCardKey(int index);
};
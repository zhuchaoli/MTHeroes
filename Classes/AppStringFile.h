//文本资源类  单例
#pragma once
#include "cocos2d.h"
#include <iostream>
using namespace std;
USING_NS_CC;

class AppStringFile
{
private:
	AppStringFile();
	static AppStringFile* m_pAppStringFile;
	void init();
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if(m_pAppStringFile != NULL)delete m_pAppStringFile;
		}
	};
	static CGarbo m_garbo;
	CCDictionary* m_pStrings;
public:
	static AppStringFile* sharedAppStringFile();
	const char* getStringForKey(const string &key);
	~AppStringFile();
};
#include "AppStringFile.h"

AppStringFile* AppStringFile::m_pAppStringFile = NULL;

AppStringFile::AppStringFile()
{

}
//将文件加载
void AppStringFile::init()
{
	m_pStrings = CCDictionary::createWithContentsOfFile("Strings.xml");
	m_pStrings->retain();//应用计数加一
}

AppStringFile* AppStringFile::sharedAppStringFile()
{
	if(!m_pAppStringFile)
	{
		m_pAppStringFile = new AppStringFile();
		m_pAppStringFile->init();
	}
	CCAssert(m_pAppStringFile,"创建文本资源应用程序失败");
	return m_pAppStringFile;
}

const char* AppStringFile::getStringForKey(const string &key)
{
	return ((CCString*)m_pStrings->objectForKey(key))->getCString();
}

AppStringFile::~AppStringFile()
{
	if(m_pStrings!=NULL)m_pStrings->release();//引用计数减一
	if(m_pStrings!=NULL)delete m_pStrings;
}


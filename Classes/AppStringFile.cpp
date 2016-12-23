#include "AppStringFile.h"

AppStringFile* AppStringFile::m_pAppStringFile = NULL;

AppStringFile::AppStringFile()
{

}
//���ļ�����
void AppStringFile::init()
{
	m_pStrings = CCDictionary::createWithContentsOfFile("Strings.xml");
	m_pStrings->retain();//Ӧ�ü�����һ
}

AppStringFile* AppStringFile::sharedAppStringFile()
{
	if(!m_pAppStringFile)
	{
		m_pAppStringFile = new AppStringFile();
		m_pAppStringFile->init();
	}
	CCAssert(m_pAppStringFile,"�����ı���ԴӦ�ó���ʧ��");
	return m_pAppStringFile;
}

const char* AppStringFile::getStringForKey(const string &key)
{
	return ((CCString*)m_pStrings->objectForKey(key))->getCString();
}

AppStringFile::~AppStringFile()
{
	if(m_pStrings!=NULL)m_pStrings->release();//���ü�����һ
	if(m_pStrings!=NULL)delete m_pStrings;
}


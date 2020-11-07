#include "DataMgr.h"

CDataMgr* CDataMgr::m_spInstance = nullptr;

CDataMgr::CDataMgr()
{

}

CDataMgr::~CDataMgr()
{

}

CDataMgr* CDataMgr::getInstance()
{
	if (!m_spInstance)
	{
		m_spInstance = new CDataMgr();
	}


	return m_spInstance;
}

void CDataMgr::addData(string strName, CDataBaseMgr* pDataMgr)
{
	if (strName.empty()||!pDataMgr)
	{
		return;
	}
	m_mapDatas.insert(pair<string, CDataBaseMgr*>(strName, pDataMgr));
}

CDataBaseMgr* CDataMgr::getData(string strName)
{
	if (strName.empty()||!m_mapDatas[strName])
	{
		return nullptr;
	}
	return m_mapDatas[strName];
}


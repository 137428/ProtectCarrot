#include "DataBase.h"
CDataBaseMgr::CDataBaseMgr()
{

}

CDataBaseMgr::~CDataBaseMgr()
{

}


void CDataBaseMgr::LoadFile(char* pFileName)
{

}

SDataBase* CDataBaseMgr::getDataByID(int nID)
{
	for (SDataBase* pData : m_vecDatas)
	{
		if (nID==pData->nID)
		{
			return pData;
		}
	}

	return nullptr;
}


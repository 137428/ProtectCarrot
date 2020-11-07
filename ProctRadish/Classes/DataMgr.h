#ifndef __DATAMGR_H__
#define __DATAMGR_H__
#include "cocos2d.h"
#include "DataBase.h"
USING_NS_CC;
class CDataMgr
{
public:
	~CDataMgr();
	static CDataMgr* getInstance();
	void addData(string strName,CDataBaseMgr* pDataMgr);
	CDataBaseMgr* getData(string strName);
private:
	CDataMgr();
	static CDataMgr* m_spInstance;
	map<string,CDataBaseMgr*> m_mapDatas;
};



#endif
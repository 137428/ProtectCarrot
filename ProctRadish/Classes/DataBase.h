#ifndef __DATABASE_H__
#define __DATABASE_H__
#include "cocos2d.h"
using namespace std;

struct SDataBase
{
	SDataBase()
	{
		nID = 0;
	}
	int nID;
};

class CDataBaseMgr
{
public:
	CDataBaseMgr();
	virtual ~CDataBaseMgr();
	virtual void LoadFile(char* pFileName);
	SDataBase*  getDataByID(int nID);
protected:
	vector<SDataBase*> m_vecDatas;
};



#endif
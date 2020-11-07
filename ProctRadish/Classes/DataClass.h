#ifndef __DATACLASS_H__
#define __DATACLASS_H__
#include "cocos2d.h"
#include "DataBase.h"
struct SLevelDt :SDataBase
{
	SLevelDt()
	{
		strViewImg = "";
		strMapImg = "";
		strCardView = "";
		nStartMoney = 0;
	}
	string strViewImg;
	string strMapImg;
	string strCardView;
	int nStartMoney;
	vector<int> MonsterID;
	vector<int> CardID;
	vector<int> vecWave;
};


class CLevelDtMgr : public CDataBaseMgr
{
public:
	CLevelDtMgr();
	~CLevelDtMgr();
	int getsize()
	{
		return m_vecDatas.size();
	}
	void setCurIndex(int nIndex)
	{
		m_nCurIndex = nIndex;

	}
	void addCurIndex()
	{
		if (m_nCurIndex < m_vecDatas.size()-1)
		{
			m_nCurIndex++;
		}
	}
	int getCurIndex()
	{
		return m_nCurIndex;
	}
	void addLockLevel()
	{
		if (m_nLockLevel<m_vecDatas.size())
		{
			m_nLockLevel = m_nCurIndex + 2;
		}
	}
	int getLockLevel()
	{
		return m_nLockLevel;

	}
	SLevelDt* getCurData()
	{
		return static_cast<SLevelDt*>(m_vecDatas[m_nCurIndex]);
	}
	void LoadFile(char* pFileName);
private:
	int m_nLockLevel;
	int m_nCurIndex;
};


struct SAniMateDt :public SDataBase
{
	SAniMateDt()
	{
		nCount = 0;
		strName = "";
	}
	int nCount;
	string strName;
};

class CAnimateDtMgr : public CDataBaseMgr
{
public:
	CAnimateDtMgr();
	~CAnimateDtMgr();
	void LoadFile(char* pFileName);

	int getsize()
	{
		return m_vecDatas.size();
	}

private:

};

struct SMonsterDt : public SDataBase
{
	SMonsterDt()
	{
		strImg = "";
		fSpeed = 0;
		AnimateID = 0;
		nMoney = 0;
	}
	string strImg;
	float fSpeed;
	int AnimateID;
	int nMoney;
};

class CMonsterDtMgr : public CDataBaseMgr
{
public:
	CMonsterDtMgr();
	~CMonsterDtMgr();
	void LoadFile(char* pFileName);

private:

};

struct SCardDt :SDataBase
{
	SCardDt()
	{
		strImg = "";
		nArmsID = 0;
	}
	string strImg;
	int nArmsID;
};

class CCardDtMgr : public CDataBaseMgr
{
public:
	CCardDtMgr();
	~CCardDtMgr();
	void LoadFile(char* pFileName);

private:

};

struct SArmsDt :SDataBase
{
	SArmsDt()
	{
		strBaseImg = "";
		nAttackID = 0;
		strImg = "";
		bRota = false;
	}
	string strBaseImg;
	string strImg;
	int nAttackID;
	int nBulletID;
	vector<int> vecMoney;
	vector<int> vecRange;
	vector<float> vecInterval;
	bool bRota;
};


class CArmsDtMgr : public CDataBaseMgr
{
public:
	CArmsDtMgr();
	~CArmsDtMgr();
	void LoadFile(char* pFileName);

private:

};

struct SBulletDt :SDataBase
{
	SBulletDt()
	{
		strImg = "";
		nDieID = 0;
		strType = "";
		nBuffId = 0;
		nMoveAnimateID = 0;
		fSpeed = 0;
		nAck = 0;
	}
	string strImg;
	string strType;
	int nDieID;
	int nBuffId;
	int nMoveAnimateID;
	float fSpeed;
	int nAck;
};

class CBulletDtMgr : public CDataBaseMgr
{
public:
	CBulletDtMgr();
	~CBulletDtMgr();
	void LoadFile(char* pFileName);

private:

}; 

struct SBuffDt :SDataBase
{
	SBuffDt()
	{
		nValue = 0;
		fTime = 0;
		nAnimateID = 0;
	}
	int nValue;
	float fTime;
	int nAnimateID;
};

class CBuffDtMgr : public CDataBaseMgr
{
public:
	CBuffDtMgr();
	~CBuffDtMgr();
	void LoadFile(char* pFileName);

private:

};
#endif
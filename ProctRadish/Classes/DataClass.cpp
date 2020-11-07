#include "DataClass.h"
#include "json/rapidjson.h"
#include "json//document.h"

USING_NS_CC;
using namespace rapidjson;

CLevelDtMgr::CLevelDtMgr()
{
	m_nCurIndex = 0;
	m_nLockLevel = 1;
}

CLevelDtMgr::~CLevelDtMgr()
{
}

void CLevelDtMgr::LoadFile(char* pFileName)
{
	string strData = FileUtils::getInstance()->getStringFromFile(pFileName);
	Document Doc;
	Doc.Parse(strData.c_str());
	for (int i = 0; i < Doc.Size();i++)
	{
		SLevelDt* pData = new SLevelDt();
		rapidjson::Value& vData = Doc[i];
		pData->nID = vData["id"].GetInt();
		pData->strViewImg = vData["viewimg"].GetString();
		pData->strMapImg = vData["mapimg"].GetString();
		pData->strCardView = vData["CardView"].GetString();
		pData->nStartMoney = vData["startMoney"].GetInt();
		rapidjson::Value& vMonsterID = vData["MonsterID"];
		for (int j = 0; j < vMonsterID.Size(); j++)
		{
			pData->MonsterID.push_back(vMonsterID[j].GetInt());
		}

		rapidjson::Value& vCardID = vData["CardID"];
		for (int m = 0; m < vCardID.Size(); m++)
		{
			pData->CardID.push_back(vCardID[m].GetInt());
		}

		rapidjson::Value& vWave = vData["wave"];
		for (int m = 0; m < vWave.Size(); m++)
		{
			pData->vecWave.push_back(vWave[m].GetInt());
		}
		m_vecDatas.push_back(pData);
	}
}

CAnimateDtMgr::CAnimateDtMgr()
{
}

CAnimateDtMgr::~CAnimateDtMgr()
{
}

void CAnimateDtMgr::LoadFile(char* pFileName)
{
	string strData = FileUtils::getInstance()->getStringFromFile(pFileName);
	Document Doc;
	Doc.Parse(strData.c_str());
	for (int i = 0; i < Doc.Size(); i++)
	{
		SAniMateDt* pData = new SAniMateDt();
		rapidjson::Value& vData = Doc[i];
		pData->nID = vData["id"].GetInt();
		pData->nCount = vData["count"].GetInt();
		pData->strName = vData["name"].GetString();
		m_vecDatas.push_back(pData);
	}
}

CMonsterDtMgr::CMonsterDtMgr()
{

}

CMonsterDtMgr::~CMonsterDtMgr()
{

}

void CMonsterDtMgr::LoadFile(char* pFileName)
{
	string strData = FileUtils::getInstance()->getStringFromFile(pFileName);
	Document Doc;
	Doc.Parse(strData.c_str());
	for (int i = 0; i < Doc.Size(); i++)
	{
		SMonsterDt* pData = new SMonsterDt();
		rapidjson::Value& vData = Doc[i];
		pData->nID = vData["id"].GetInt();
		pData->strImg = vData["img"].GetString();
		pData->fSpeed = vData["speed"].GetDouble();
		pData->AnimateID = vData["animateID"].GetInt();
		pData->nMoney = vData["Money"].GetInt();
		m_vecDatas.push_back(pData);
	}
}

CCardDtMgr::CCardDtMgr()
{

}

CCardDtMgr::~CCardDtMgr()
{

}

void CCardDtMgr::LoadFile(char* pFileName)
{
	string strData = FileUtils::getInstance()->getStringFromFile(pFileName);
	Document Doc;
	Doc.Parse(strData.c_str());
	for (int i = 0; i < Doc.Size(); i++)
	{
		SCardDt* pData = new SCardDt();
		rapidjson::Value& vData = Doc[i];
		pData->nID = vData["id"].GetInt();
		pData->strImg = vData["img"].GetString();
		pData->nArmsID = vData["ArmsID"].GetInt();
		m_vecDatas.push_back(pData);
	}
}

CArmsDtMgr::CArmsDtMgr()
{

}

CArmsDtMgr::~CArmsDtMgr()
{

}

void CArmsDtMgr::LoadFile(char* pFileName)
{
	string strData = FileUtils::getInstance()->getStringFromFile(pFileName);
	Document Doc;
	Doc.Parse(strData.c_str());
	for (int i = 0; i < Doc.Size(); i++)
	{
		SArmsDt* pData = new SArmsDt();
		rapidjson::Value& vData = Doc[i];
		pData->nID = vData["id"].GetInt();
		pData->strImg = vData["Img"].GetString();
		pData->nAttackID = vData["AttackID"].GetInt();
		pData->strBaseImg = vData["BaseImg"].GetString();
		pData->nBulletID = vData["BulletID"].GetInt();
		pData->bRota = vData["Rota"].GetInt();
		rapidjson::Value& vMoney = vData["upgrade"];
		for (int i = 0; i < vMoney.Size();i++)
		{
			pData->vecMoney.push_back(vMoney[i].GetInt());
		}

		rapidjson::Value& vRange = vData["range"];
		for (int i = 0; i < vRange.Size(); i++)
		{
			pData->vecRange.push_back(vRange[i].GetInt());
		}

		rapidjson::Value& vInterval = vData["Interval"];
		for (int i = 0; i < vInterval.Size(); i++)
		{
			pData->vecInterval.push_back(vInterval[i].GetDouble());
		}

		m_vecDatas.push_back(pData);
	}
}

CBulletDtMgr::CBulletDtMgr()
{

}

CBulletDtMgr::~CBulletDtMgr()
{

}

void CBulletDtMgr::LoadFile(char* pFileName)
{
	string strData = FileUtils::getInstance()->getStringFromFile(pFileName);
	Document Doc;
	Doc.Parse(strData.c_str());
	for (int i = 0; i < Doc.Size(); i++)
	{
		SBulletDt* pData = new SBulletDt();
		rapidjson::Value& vData = Doc[i];
		pData->nID = vData["id"].GetInt();
		pData->strImg = vData["Img"].GetString();
		pData->strType = vData["Type"].GetString();
		pData->nDieID = vData["die"].GetInt();
		pData->nBuffId = vData["buffID"].GetInt();
		pData->nMoveAnimateID = vData["moveAnimateID"].GetInt();
		pData->fSpeed = vData["speed"].GetDouble();
		pData->nAck = vData["ack"].GetInt();
		m_vecDatas.push_back(pData);
	}
}

CBuffDtMgr::CBuffDtMgr()
{

}

CBuffDtMgr::~CBuffDtMgr()
{

}

void CBuffDtMgr::LoadFile(char* pFileName)
{
	string strData = FileUtils::getInstance()->getStringFromFile(pFileName);
	Document Doc;
	Doc.Parse(strData.c_str());
	for (int i = 0; i < Doc.Size(); i++)
	{
		SBuffDt* pData = new SBuffDt();
		rapidjson::Value& vData = Doc[i];
		pData->nID = vData["id"].GetInt();
		pData->nValue = vData["value"].GetInt();
		pData->fTime = vData["time"].GetDouble();
		pData->nAnimateID = vData["animateID"].GetDouble();
		m_vecDatas.push_back(pData);
	}
}
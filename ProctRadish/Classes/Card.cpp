#include "Card.h"
#include "DataClass.h"
#include "DataMgr.h"
CCard::CCard()
{

}

CCard::~CCard()
{

}

bool CCard::initWithData(SCardDt* pCard)
{
	if (!Sprite::initWithSpriteFrameName(StringUtils::format(pCard->strImg.c_str(), 1)))
	{
		return false;
	}
	m_nArmsID = pCard->nArmsID;
	m_strName = pCard->strImg;

	CArmsDtMgr* pArmsDtMgr = static_cast<CArmsDtMgr*>(CDataMgr::getInstance()->getData("ArmsMgr"));//拿到卡片数据管理者
	SArmsDt* pArmsDt = static_cast<SArmsDt*>(pArmsDtMgr->getDataByID(m_nArmsID));
	m_nMoney = pArmsDt->vecMoney[0];
	return true;
}

CCard* CCard::createWithData(SCardDt* pCard)
{
	CCard* pRef = new CCard();
	if (pRef&&pRef->initWithData(pCard))
	{
		pRef->autorelease();
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

void CCard::setSprite(int nMoney)
{
	if (nMoney>=m_nMoney)
	{
		SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(m_strName.c_str(),1));
		this->setSpriteFrame(pFrame);
	}
	else
	{
		SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(m_strName.c_str(), 0));
		this->setSpriteFrame(pFrame);
	}
}

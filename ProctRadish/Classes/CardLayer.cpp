#include "CardLayer.h"
#include "DataMgr.h"
#include "DataClass.h"
#include "GameScene.h"
#include "Card.h"
CCardLayer::CCardLayer()
{

}

CCardLayer::~CCardLayer()
{

}

bool CCardLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	Sprite* pSelect = Sprite::createWithSpriteFrameName("select_01.png");
	this->addChild(pSelect);
	this->createCard();
	this->setVisible(false);
	return true;
}

void CCardLayer::createCard()
{
	m_pCardColony = ::Sprite::create();
	CLevelDtMgr* pLevelDtMgr = static_cast<CLevelDtMgr*>(CDataMgr::getInstance()->getData("LevelMgr"));//拿到关卡数据管理者	
	CCardDtMgr* pCardDtMgr = static_cast<CCardDtMgr*>(CDataMgr::getInstance()->getData("CardMgr"));//拿到卡片数据管理者	
	for (int i = 0; i < pLevelDtMgr->getCurData()->CardID.size();i++)
	{
		int nID = pLevelDtMgr->getCurData()->CardID[i];
		CCard* pCard = CCard::createWithData(static_cast<SCardDt*>(pCardDtMgr->getDataByID(nID)));
		pCard->setPosition(i*pCard->getContentSize().width, 0);
		pCard->setAnchorPoint(Vec2::ZERO);
		m_pCardColony->addChild(pCard);
		m_vecCard.push_back(pCard);
	}
	m_pCardColony->setContentSize(Size((m_vecCard[0]->getContentSize().width)*m_vecCard.size(), m_vecCard[0]->getContentSize().height));
	m_pCardColony->setAnchorPoint(Vec2::ZERO);
	this->addChild(m_pCardColony);
}

void CCardLayer::clickEvent(Vec2 clickPos)
{
	Vec2 tiledPos = CGameScene::getInstance()->getGameMap()->getTiledByPos(clickPos);
	if (!this->isVisible() && !CGameScene::getInstance()->getGameMap()->isInLayer("path", tiledPos))
	{
		this->setCardSprite(CGameScene::getInstance()->getUILayer()->getMoney());
		Vec2 TiledPos=CGameScene::getInstance()->getGameMap()->getTiledByPos(clickPos);
		Vec2 Pos = CGameScene::getInstance()->getGameMap()->getPixelByTiledPos(tiledPos);
		this->setPosition(Pos);
		this->setVisible(true);
		if (clickPos.y>WINSIZE.height - m_vecCard[0]->getContentSize().height)
		{
			m_pCardColony->setAnchorPoint(Vec2(0,1));
		}
		if (clickPos.x>WINSIZE.width - (m_vecCard[0]->getContentSize().width)*m_vecCard.size())
		{
			m_pCardColony->setAnchorPoint(m_pCardColony->getAnchorPoint()+Vec2(1, 0));
		}
	}	
	else if (this->isVisible())
	{
		CCard* pCard = this->clickCard(clickPos);
		if (pCard//点中卡片
			&&CGameScene::getInstance()->getUILayer()->getMoney()>=pCard->getMoney())//拥有金币大于卡片所需金币
		{
			//创建武器
			CGameScene::getInstance()->getArmsLayer()->createArms(pCard->getArmsID(),this->getPosition());
		}
		this->setVisible(false);
		m_pCardColony->setAnchorPoint(Vec2(0, 0));
	}
}

CCard* CCardLayer::clickCard(Vec2 clickPos)
{
	for (CCard* pCard : m_vecCard)
	{
		if (pCard->getBoundingBox().containsPoint(m_pCardColony->convertToNodeSpace(clickPos)))
		{
			return pCard;
		}
	}
	return nullptr;
}

void CCardLayer::setCardSprite(int nMoney)
{
	for (CCard* pCard:m_vecCard)
	{
		pCard->setSprite(nMoney);
	}
}


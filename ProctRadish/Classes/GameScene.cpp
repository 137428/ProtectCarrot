#include "GameScene.h"
#include "DataMgr.h"
#include "DataClass.h"
#include "TouchLayer.h"
#include "Monster.h"
CGameScene* CGameScene::m_spInstance = nullptr;
CGameScene::CGameScene()
{

}

CGameScene::~CGameScene()
{

}

bool CGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	CLevelDtMgr* pLevelDtMgr=static_cast<CLevelDtMgr*>(CDataMgr::getInstance()->getData("LevelMgr"));//拿到关卡数据管理者
	SLevelDt* pLevelDt = pLevelDtMgr->getCurData();

	m_nMoney = 10000;

	m_pGameMap = CGameMap::createWithImgPath(pLevelDt->strMapImg);
	this->addChild(m_pGameMap);

	CMonster::setPath(m_pGameMap->getInitPos());


	m_pMonsterLayer = CMonsterLayer::create();
	this->addChild(m_pMonsterLayer);

	m_pAnimateLayer = CAnimateLayer::create();
	this->addChild(m_pAnimateLayer);

	this->addChild(CTouchLayer::create());

	m_pBulletLayer = CBulletLayer::create();
	this->addChild(m_pBulletLayer);

	m_pArmsLayer = CArmsLayer::create();
	this->addChild(m_pArmsLayer);


	m_pBuffLayer = CBuffLayer::create();
	this->addChild(m_pBuffLayer);


	m_pRadish = CRadish::create();
	m_pRadish->setPosition(m_pGameMap->getLastTiledPos());
	this->addChild(m_pRadish);

	m_pUILayer = CUILayer::create();
	this->addChild(m_pUILayer);

	m_pCardLayer = CCardLayer::create();
	this->addChild(m_pCardLayer);

	m_pUpCardLayer = CUpCardLayer::create();
	this->addChild(m_pUpCardLayer);

	Sprite* pSprite = Sprite::create("Map/Radish01_01.png");
	pSprite->setPosition(m_pGameMap->getFirstTiledPos());
	this->addChild(pSprite);

	this->scheduleUpdate();
	return true;
}

CGameScene* CGameScene::getInstance()
{
	if (!m_spInstance)
	{
		m_spInstance =CGameScene::create();
	}
	return m_spInstance;
}

void CGameScene::update(float delta)
{
	//拿到所有子弹
	Vector<Node*> VecBullet = m_pBulletLayer->getChildren();
	for (Node* pBulletNode : VecBullet)
	{
		if (pBulletNode->getTag() != 1)
		{
			//拿到所有敌人
			Vector<Node*> VecMonster = m_pMonsterLayer->getChildren();
			for (Node* pMonsterNode : VecMonster)
			{
				CMonster* pMonster = static_cast<CMonster*>(pMonsterNode);
				CBulletBase* pBullet = static_cast<CBulletBase*>(pBulletNode);
				Vec2 Pos = Vec2(pMonster->getPosition().x - pMonster->getModel()->getContentSize().width / 2, pMonster->getPosition().y - pMonster->getModel()->getContentSize().height / 2);
				Rect newRect = Rect(this->convertToNodeSpace(Pos),pMonster->getModel()->getContentSize());
				if (newRect.intersectsCircle(pBullet->getPosition(),10))
				{
					pBullet->collisions(pMonsterNode);
					break;
				}
			}
		}
	}
}

void CGameScene::deletInstance()
{
	CGameScene::getInstance()->unscheduleUpdate();
	CGameScene::getInstance()->removeAllChildren();
	m_spInstance = nullptr;
}


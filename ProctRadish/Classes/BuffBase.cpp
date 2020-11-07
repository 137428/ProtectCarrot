#include "BuffBase.h"
#include "GameScene.h"
CBuffBase::CBuffBase()
{

}

CBuffBase::~CBuffBase()
{

}

bool CBuffBase::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void CBuffBase::update(float delta)
{

}

void CBuffBase::addBuffNode(Node* pNode, SBuffDt* pBuff)
{
	map<Node*, SData*>::iterator iter = m_mapBuff.find(pNode);
	if (iter!=m_mapBuff.end())
	{
		m_mapBuff[pNode]->fTime = pBuff->fTime;
	}
	else
	{
		SData* pData = new SData();
		pData->fTime = pBuff->fTime;
		pData->nValue = pBuff->nValue;
		pData->pSprite = Sprite::create();
		CGameScene::getInstance()->getAnimateLayer()->changeAction(pData->pSprite, pBuff->nAnimateID, true, 0.1f);
		pData->pSprite->setPositionY(static_cast<CMonster*>(pNode)->getContentSize().height / 2);
		pNode->addChild(pData->pSprite);
		m_mapBuff[pNode] = pData;
	}
}

void CBuffBase::removeBuffNode(Node* pNode)
{
	map<Node*, SData*>::iterator iter = m_mapBuff.find(pNode);
	if (iter != m_mapBuff.end())
	{
		m_mapBuff[pNode]->pSprite->stopAllActions();
		m_mapBuff[pNode]->pSprite->removeFromParent();
		m_mapBuff.erase(pNode);
	}
}


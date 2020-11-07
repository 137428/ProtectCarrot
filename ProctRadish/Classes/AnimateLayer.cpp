#include "AnimateLayer.h"
CAnimateLayer::CAnimateLayer()
{

}

CAnimateLayer::~CAnimateLayer()
{

}

bool CAnimateLayer::init()
{
	if (!Node::init())
	{
		return false;
	}


	m_pAnimateDtMgr = static_cast<CAnimateDtMgr*>(CDataMgr::getInstance()->getData("AnimateMgr"));//拿到动画数据管理者
	return true;
}


void CAnimateLayer::changeAction(Sprite* pSprite, int nID, bool bEver, float fDelayTime)
{
	if (nID<3000)
	{
		return;
	}
	pSprite->stopAllActionsByTag(1);

	SAniMateDt* pData = static_cast<SAniMateDt*>(m_pAnimateDtMgr->getDataByID(nID));

	Animation* pAnimation = Animation::create();//动画

	for (int j = 1; j <= pData->nCount; j++)
	{
		SpriteFrame* pSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(pData->strName.c_str(), j));
		pAnimation->addSpriteFrame(pSpriteFrame);
	}

	pAnimation->setDelayPerUnit(fDelayTime);
	//pAnimation->setRestoreOriginalFrame(true);
	Animate* pAnimate = Animate::create(pAnimation);
	if (bEver)
	{
		RepeatForever* pRe = RepeatForever::create(pAnimate);
		//pRe->setTag(1);
		pSprite->runAction(pRe);
	}
	else
	{
		pAnimate->setTag(1);
		pSprite->runAction(pAnimate);
	}
}

Animate* CAnimateLayer::getAnimate(int nID)
{
	SAniMateDt* pData = static_cast<SAniMateDt*>(m_pAnimateDtMgr->getDataByID(nID));

	Animation* pAnimation = Animation::create();//动画

	for (int j = 1; j <= pData->nCount; j++)
	{
		SpriteFrame* pSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(pData->strName.c_str(), j));
		pAnimation->addSpriteFrame(pSpriteFrame);
	}

	pAnimation->setDelayPerUnit(0.1f);
	pAnimation->setRestoreOriginalFrame(true);
	Animate* pAnimate = Animate::create(pAnimation);
	pAnimate->setTag(1);
	return pAnimate;
}

void CAnimateLayer::createAnimate(Vec2 pos, int nID)
{
	Sprite* pSprite = Sprite::create();
	SAniMateDt* pData = static_cast<SAniMateDt*>(m_pAnimateDtMgr->getDataByID(nID));

	Animation* pAnimation = Animation::create();//动画

	for (int j = 1; j <= pData->nCount; j++)
	{
		SpriteFrame* pSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(pData->strName.c_str(), j));
		pAnimation->addSpriteFrame(pSpriteFrame);
	}

	pAnimation->setDelayPerUnit(0.1f);
	Animate* pAnimate = Animate::create(pAnimation);
	pSprite->setPosition(pos);
	pSprite->runAction(Sequence::createWithTwoActions(pAnimate,RemoveSelf::create()));
	this->addChild(pSprite);
}


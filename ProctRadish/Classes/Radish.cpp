#include "Radish.h"
#include "GameScene.h"
CRadish::CRadish()
{
}

CRadish::~CRadish()
{
}

bool CRadish::init()
{
	if (!Node::init())
	{
		return false;
	}
	m_nHP = 10;
	m_pHp = Sprite::createWithSpriteFrameName(StringUtils::format("BossHP%02d.png", m_nHP));
	m_pModel = Sprite::createWithSpriteFrameName(StringUtils::format("hlb%d.png", m_nHP));
	m_pHp->setPosition(80,0);
	this->addChild(m_pHp);
	this->addChild(m_pModel);
	this->schedule([=](float){
		if (m_nHP<10)
		{
			this->unschedule("Move");
			return;
		}
		Animate* pAnimate=CGameScene::getInstance()->getAnimateLayer()->getAnimate(3023);
		pAnimate->getAnimation()->setRestoreOriginalFrame(true);
		m_pModel->stopAllActions();
		m_pModel->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hlb10.png"));
		m_pModel->runAction(pAnimate);
	},3.0f,"Move");
	return true;
}

bool CRadish::Damage()
{
	m_nHP--;
	if (m_nHP<=0)
	{
		CGameScene::getInstance()->getMonsterLayer()->GameOver();
		return true;
	}
	m_pModel->stopAllActions();
	std::string strName = StringUtils::format("BossHP%02d.png",m_nHP );
	SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(strName);
	m_pHp->setSpriteFrame(pFrame);

	strName = StringUtils::format("hlb%d.png", m_nHP == 7 || m_nHP == 5 ? m_nHP + 1 : m_nHP);
	pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(strName);
	m_pModel->setSpriteFrame(pFrame);
	return false;
}

void CRadish::clickEvent(Vec2 clickPos)
{
	if (m_nHP>=10
		&&m_pModel->getBoundingBox().containsPoint(this->convertToNodeSpace(clickPos)))
	{
		Animate* pAnimate = CGameScene::getInstance()->getAnimateLayer()->getAnimate(3022);
		pAnimate->getAnimation()->setRestoreOriginalFrame(true);
		m_pModel->stopAllActions();
		m_pModel->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hlb10.png"));
		m_pModel->runAction(pAnimate);
	}
}

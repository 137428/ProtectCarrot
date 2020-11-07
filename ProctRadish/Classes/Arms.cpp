#include "Arms.h"
#include "GameScene.h"
CArms::CArms()
{

}

CArms::~CArms()
{

}

bool CArms::initWithData(SArmsDt* pArms)
{
	if (!Sprite::init())
	{
		return false;
	}
	m_pArmsDt = pArms;
	m_bAttack = false;
	m_nGrade = 1;
	m_pLastBullet = nullptr;
	m_pBaseSprite = Sprite::createWithSpriteFrameName(StringUtils::format(pArms->strBaseImg.c_str(), m_nGrade));
	m_pSprite = Sprite::createWithSpriteFrameName(StringUtils::format(pArms->strImg.c_str(), m_nGrade));
	this->addChild(m_pBaseSprite);
	this->addChild(m_pSprite);
	this->scheduleUpdate();

	return true;
}

CArms* CArms::createWithData(SArmsDt* pArms)
{
	CArms* pRef = new CArms();
	if (pRef&&pRef->initWithData(pArms))
	{
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

void CArms::fire(Node* pNode)
{
	if (m_pArmsDt->nBulletID>6100)
	{
		CGameScene::getInstance()->getAnimateLayer()->changeAction(m_pSprite, m_pArmsDt->nAttackID + m_nGrade - 1, true, 0.1f);
	}
	else
	{
		CGameScene::getInstance()->getAnimateLayer()->changeAction(m_pSprite, m_pArmsDt->nAttackID + m_nGrade - 1, false, 0.1f);
	}
	
	m_pLastBullet=CGameScene::getInstance()->getBulletLayer()->addBullet(m_pArmsDt->nBulletID, this->getPosition(), pNode, m_pArmsDt->vecRange[m_nGrade-1]*1.8,m_nGrade);
	m_bAttack = false;

}

void CArms::update(float delta)
{
	CMonster* pMonster = CGameScene::getInstance()->getMonsterLayer()->getMonster(m_pArmsDt->vecRange[m_nGrade - 1]*1.8, this->getPosition());
	if (pMonster)
	{
		if (m_pArmsDt->bRota)
		{
			Vec2 deltaPos = pMonster->getPosition() - this->getPosition();
			float fAngel = deltaPos.getAngle(Vec2(0, 1));
			m_pSprite->setRotation(CC_RADIANS_TO_DEGREES(fAngel));
		}
		if (!m_bAttack)
		{
			this->fire(pMonster);
			m_bAttack = true;
			if (m_pArmsDt->nBulletID<6100)
			{
				this->schedule([=](float){
					m_bAttack = false;
				}, m_pArmsDt->vecInterval[m_nGrade-1], "fire");
			}
		}

	}
	else
	{
		m_pSprite->stopAllActions();
		m_bAttack = false;
		this->unschedule("fire");
	}
}

void CArms::upgrade()
{
	m_pSprite->stopAllActions();
	m_nGrade++;
	SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(m_pArmsDt->strImg.c_str(), m_nGrade));
	m_pSprite->setSpriteFrame(pFrame);

	SpriteFrame* pFrameBase = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(m_pArmsDt->strBaseImg.c_str(), m_nGrade));
	if (pFrameBase)
	{
		m_pBaseSprite->setSpriteFrame(pFrameBase);
	}

	if (m_pLastBullet&&m_pLastBullet->getTag()==1)
	{
		m_pLastBullet->removeFromParent();
		m_bAttack =false;
	}
}


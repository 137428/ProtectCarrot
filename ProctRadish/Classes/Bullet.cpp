#include "Bullet.h"
#include "GameScene.h"
#include "Monster.h"
CBulletCommon::CBulletCommon()
{

}

CBulletCommon::~CBulletCommon()
{

}


bool CBulletCommon::initWithData(SBulletDt* pBullet, int nGrade)
{
	if (!CBulletBase::initWithData(pBullet,nGrade))
	{
		return false;
	}
	this->scheduleUpdate();
	return true;
}


CBulletCommon* CBulletCommon::createWithData(SBulletDt* pBullet,int nGrade)
{
	CBulletCommon* pRef = new CBulletCommon();
	if (pRef&&pRef->initWithData(pBullet, nGrade))
	{
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

void CBulletCommon::update(float delta)
{
	CBulletBase::update(delta);
}

void CBulletCommon::collisions(Node* pNode)
{
	CMonster* pMonster = static_cast<CMonster*>(pNode);
	if (pMonster->Damage(-m_nAck))
	{
		pMonster->removeMonster();
	}
	CGameScene::getInstance()->getAnimateLayer()->createAnimate(this->getPosition(), m_nDieID);
	this->removeFromParent();

}

CBulletThrough::CBulletThrough()
{

}

CBulletThrough::~CBulletThrough()
{

}


bool CBulletThrough::initWithData(SBulletDt* pBullet, int nGrade)
{
	if (!CBulletBase::initWithData(pBullet, nGrade))
	{
		return false;
	}
	this->scheduleUpdate();
	return true;
}


CBulletThrough* CBulletThrough::createWithData(SBulletDt* pBullet, int nGrade)
{
	CBulletThrough* pRef = new CBulletThrough();
	if (pRef&&pRef->initWithData(pBullet, nGrade))
	{
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

void CBulletThrough::update(float delta)
{
	CBulletBase::update(delta);
}

void CBulletThrough::collisions(Node* pNode)
{
	if (m_pAckNode!=pNode)
	{
		m_pAckNode = pNode;
		CMonster* pMonster = static_cast<CMonster*>(m_pAckNode);
		CGameScene::getInstance()->getAnimateLayer()->createAnimate(this->getPosition(), m_nDieID);
		if (pMonster->Damage(-m_nAck))
		{
			pMonster->removeMonster();
		}
	}
}

CBulletRadial::CBulletRadial()
{

}

CBulletRadial::~CBulletRadial()
{

}


bool CBulletRadial::initWithData(SBulletDt* pBullet, int nGrade)
{
	if (!CBulletBase::initWithData(pBullet, nGrade))
	{
		return false;
	}
	this->setAnchorPoint(Vec2(0.5, 0));
	this->setTag(1);
	this->scheduleUpdate();
	m_pSprite = Sprite::create();
	m_pSprite->setVisible(false);
	this->addChild(m_pSprite);
	return true;
}


CBulletRadial* CBulletRadial::createWithData(SBulletDt* pBullet, int nGrade)
{
	CBulletRadial* pRef = new CBulletRadial();
	if (pRef&&pRef->initWithData(pBullet, nGrade))
	{
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

void CBulletRadial::update(float delta)
{
	CMonster* pMonster=CGameScene::getInstance()->getMonsterLayer()->getMonster(m_fAckRange, this->getPosition());
	if (pMonster)
	{
		if (!m_pSprite->isVisible())
		{
			m_pSprite->setVisible(true);
			CGameScene::getInstance()->getAnimateLayer()->changeAction(m_pSprite, m_nDieID,true,0.5f);
		}
		m_pSprite->setPosition(this->convertToNodeSpace(pMonster->getPosition()));
		if (pMonster->Damage(-m_nAck))
		{
			pMonster->removeMonster();
			return;
		}
		Vec2 Pos = pMonster->getPosition() - this->getPosition();
		float fAngel = Pos.getAngle(Vec2(0,1));
		this->setRotation(CC_RADIANS_TO_DEGREES(fAngel));
		float fY = Pos.getLength() / this->getContentSize().height;
		this->setScaleY(fY);
	}
	else
	{
		Vector<Node*> VecArms = CGameScene::getInstance()->getArmsLayer()->getChildren();
		for (Node* pNode : VecArms)
		{
			CArms* pArms = static_cast<CArms*>(pNode);
			if (this==pArms->getLastBullet())
			{
				pArms->setLastBullet(nullptr);
				break;
			}
		}
		this->removeFromParent();
	}
}

CBulletStatic::CBulletStatic()
{

}

CBulletStatic::~CBulletStatic()
{

}

bool CBulletStatic::initWithData(SBulletDt* pBullet, int nGrade)
{
	if (!CBulletBase::initWithData(pBullet, nGrade))
	{
		return false;
	}
	return true;
}

void CBulletStatic::update(float delta)
{
	vector<CMonster*> vecMonster = CGameScene::getInstance()->getMonsterLayer()->getMonsterVec(m_fAckRange, this->getPosition());
	for (int i = 0; i < vecMonster.size();i++)
	{
		if (vecMonster[i]->Damage(-m_nAck))
		{
			vecMonster[i]->removeMonster();
			break;
		}
		CGameScene::getInstance()->getBuffLayer()->addBuff(vecMonster[i], m_nBuffID);
	}
}

CBulletStatic* CBulletStatic::createWithData(SBulletDt* pBullet, int nGrade)
{
	CBulletStatic* pRef = new CBulletStatic();
	if (pRef&&pRef->initWithData(pBullet, nGrade))
	{
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

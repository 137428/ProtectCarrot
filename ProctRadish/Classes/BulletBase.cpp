#include "BulletBase.h"
#include "GameScene.h"
CBulletBase::CBulletBase()
{

}

CBulletBase::~CBulletBase()
{

}

bool CBulletBase::initWithData(SBulletDt* pBullet, int nGrand)
{
	if (!Sprite::initWithSpriteFrameName(StringUtils::format(pBullet->strImg.c_str(),nGrand)))
	{
		return false;
	}
	m_nDieID = pBullet->nDieID;
	m_fSpeed = pBullet->fSpeed;
	m_nBuffID = pBullet->nBuffId;
	m_nAck = pBullet->nAck;
	return true;
}

void CBulletBase::update(float delta)
{
	Vec2 pos = this->getPosition();
	pos.x += m_fSpeed*delta*m_vDir.x;
	pos.y += m_fSpeed*delta*m_vDir.y;
	this->setPosition(pos);
}

void CBulletBase::collisions(Node* pNode)
{

}


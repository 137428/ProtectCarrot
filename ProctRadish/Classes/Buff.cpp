#include "Buff.h"
#include "Monster.h"
CBuffSpeed::CBuffSpeed()
{

}

CBuffSpeed::~CBuffSpeed()
{

}

bool CBuffSpeed::init()
{
	if (!CBuffBase::init())
	{
		return false;
	}
	return true;
}

void CBuffSpeed::update(float delta)
{
	if (!m_mapBuff.empty())
	{
		for (map<Node*, SData*>::iterator iter = m_mapBuff.begin(); iter != m_mapBuff.end(); iter++)
		{
			iter->second->fTime -= delta;
			static_cast<CMonster*>(iter->first)->setSpeed(iter->second->nValue);
			if (iter->second->fTime <= 0)
			{
				static_cast<CMonster*>(iter->first)->setSpeed(static_cast<CMonster*>(iter->first)->getSaveSpeed());
				iter->second->pSprite->stopAllActions();
				iter->second->pSprite->removeFromParent();
				iter = m_mapBuff.erase(iter);
			}
		}
	}
}


CBuffHurt::CBuffHurt()
{

}

CBuffHurt::~CBuffHurt()
{

}

bool CBuffHurt::init()
{
	if (!CBuffBase::init())
	{
		return false;
	}

	return true;
}

void CBuffHurt::update(float delta)
{
	if (!m_mapBuff.empty())
	{
		for (map<Node*, SData*>::iterator iter = m_mapBuff.begin(); iter != m_mapBuff.end(); iter++)
		{
			iter->second->fTime -= delta;
			if (static_cast<CMonster*>(iter->first)->Damage(-iter->second->nValue))
			{
				static_cast<CMonster*>(iter->first)->removeMonster();
				break;
			}
			if (iter->second->fTime <= 0)
			{
				iter->second->pSprite->stopAllActions();
				iter->second->pSprite->removeFromParent();
				iter = m_mapBuff.erase(iter);
			}
		}
	}
}

#include "RoleBase.h"
CRoleBase::CRoleBase()
{

}

CRoleBase::~CRoleBase()
{

}

bool CRoleBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	this->createHpBar();
	return true;
}

void CRoleBase::createHpBar()
{
	Sprite* pHpBg = Sprite::createWithSpriteFrameName("MonsterHP02.png");//创建血条背景
	pHpBg->setPosition(Vec2(0, pHpBg->getContentSize().height / 2));
	m_pHpBar =ProgressTimer::create(Sprite::createWithSpriteFrameName("MonsterHP01.png"));//创建精灵条
	m_pHpBar->setType(ProgressTimer::Type::BAR);//设置为条形
	m_pHpBar->setMidpoint(Vec2(0,0));//设置起始位置
	m_pHpBar->setBarChangeRate(Vec2(1,0));
	m_pHpBar->setPercentage(100);
	m_pHpBar->setPosition(Vec2(0,pHpBg->getContentSize().height/2));
	m_pHpNode = Node::create();
	m_pHpNode->addChild(pHpBg);
	m_pHpNode->addChild(m_pHpBar);
	this->addChild(m_pHpNode);
}

bool CRoleBase::Damage(int nDamage)
{
	m_nHp += nDamage;
	if (m_nHp<=0)
	{
		m_pHpBar->setPercentage(0);
		return true;
	}
	m_pHpBar->setPercentage((float)m_nHp / m_nMaxHp * 100);
	return false;
}


#ifndef __ROLEBASE_H__
#define __ROLEBASE_H__
#include "cocos2d.h"
USING_NS_CC;
class CRoleBase : public Sprite
{
public:
	CRoleBase();
	~CRoleBase();
	virtual bool init();
	void createHpBar();
	bool Damage(int nDamage);
	CC_SYNTHESIZE(int ,m_nHp,Hp);
	CC_SYNTHESIZE(int, m_nMaxHp, MaxHp);
	CC_SYNTHESIZE(Sprite*, m_pModel, Model);
	CC_SYNTHESIZE(ProgressTimer* ,m_pHpBar,HpBar);//血条精灵
	CC_SYNTHESIZE(Node*, m_pHpNode, HpNode);//血条节点
};
#endif
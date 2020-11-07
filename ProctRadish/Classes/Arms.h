#ifndef __ARMS_H__
#define __ARMS_H__
#include "cocos2d.h"
#include "DataClass.h"
#include "Monster.h"
#include "BulletBase.h"
USING_NS_CC;
class CArms : public Sprite
{
public:
	CArms();
	~CArms();
	bool initWithData(SArmsDt* pArms);
	void fire(Node* pNode);
	virtual void update(float delta);
	void upgrade();
	static CArms* createWithData(SArmsDt* pArms);
	CC_SYNTHESIZE(int, m_nGrade,Grade);
	CC_SYNTHESIZE(SArmsDt*, m_pArmsDt, ArmsDt);
	CC_SYNTHESIZE(CBulletBase*,m_pLastBullet,LastBullet);
private:
	Sprite* m_pBaseSprite; 
	Sprite* m_pSprite;
	bool m_bAttack;
};


#endif
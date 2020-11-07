#ifndef __BULLETBASE_H__
#define __BULLETBASE_H__
#include "cocos2d.h"
#include "DataClass.h"
USING_NS_CC;
class CBulletBase : public Sprite
{
public:
	CBulletBase();
	~CBulletBase();
	bool initWithData(SBulletDt* pBullet, int nGrand);
	virtual void update(float delta);
	virtual void collisions(Node* pNode);
	CC_SYNTHESIZE(float, m_fSpeed, Speed);
	CC_SYNTHESIZE(Vec2, m_vDir, Dir);
	CC_SYNTHESIZE(float, m_fAckRange, AckRange);
	CC_SYNTHESIZE(int, m_nBuffID, BuffID);
	CC_SYNTHESIZE(int, m_nAck, Ack);
	CC_SYNTHESIZE(int, m_nDieID,DieId);
private:
};


#endif
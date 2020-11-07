#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"
#include "DataClass.h"
#include "BulletBase.h"
USING_NS_CC;
class CBulletCommon : public CBulletBase
{
public:
	CBulletCommon();
	~CBulletCommon();
	bool initWithData(SBulletDt* pBullet, int nGrade);
	virtual void update(float delta);
	virtual void collisions(Node* pNode);
	static CBulletCommon* createWithData(SBulletDt* pBullet, int nGrade);
private:
};

class CBulletThrough : public CBulletBase
{
public:
	CBulletThrough();
	~CBulletThrough();
	bool initWithData(SBulletDt* pBullet, int nGrade);
	virtual void update(float delta);
	virtual void collisions(Node* pNode);
	static CBulletThrough* createWithData(SBulletDt* pBullet, int nGrade);
	CC_SYNTHESIZE(Node*, m_pAckNode, AckNode);
private:
};

class CBulletRadial : public CBulletBase
{
public:
	CBulletRadial();
	~CBulletRadial();
	bool initWithData(SBulletDt* pBullet, int nGrade);
	virtual void update(float delta);
	static CBulletRadial* createWithData(SBulletDt* pBullet, int nGrade);
private:
	Sprite* m_pSprite;
};


class CBulletStatic : public CBulletBase
{
public:
	CBulletStatic();
	~CBulletStatic();
	bool initWithData(SBulletDt* pBullet, int nGrade);
	virtual void update(float delta);
	static CBulletStatic* createWithData(SBulletDt* pBullet, int nGrade);
private:
	Sprite* m_pSprite;
};

#endif
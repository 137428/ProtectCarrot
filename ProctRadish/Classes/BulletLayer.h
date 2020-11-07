#ifndef __BULLETLAYER_H__
#define __BULLETLAYER_H__
#include "cocos2d.h"
#include "DataClass.h"
#include "DataMgr.h"
#include "BulletBase.h"

typedef function<CBulletBase*(SBulletDt* pBulletDt, int nGrand)> bulletCallBack;

USING_NS_CC;
class CBulletLayer : public Node
{
public:
	CBulletLayer();
	~CBulletLayer();
	virtual bool init();
	void inintCallBack();
	CBulletBase* addBullet(int nID, Vec2 pos, Node* pNode, float fAckRange, int nGrade);
	CREATE_FUNC(CBulletLayer);
private:
	std::map<string, bulletCallBack>m_mapCallBack;
};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
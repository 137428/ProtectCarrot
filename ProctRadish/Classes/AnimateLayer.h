#ifndef __ANIMATELAYER_H__
#define __ANIMATELAYER_H__
#include "cocos2d.h"
#include "DataClass.h"
#include "DataMgr.h"
USING_NS_CC;
class CAnimateLayer : public Node
{
public:
	CAnimateLayer();
	~CAnimateLayer();
	virtual bool init();
	void changeAction(Sprite* pSprite, int nID, bool bEver, float fDelayTime);
	Animate* getAnimate(int nID);
	void createAnimate(Vec2 pos,int nID);
	CREATE_FUNC(CAnimateLayer);
private:
	CAnimateDtMgr* m_pAnimateDtMgr;
};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
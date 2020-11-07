#ifndef __ARMSLAYER_H__
#define __ARMSLAYER_H__
#include "cocos2d.h"
#include "DataClass.h"
#include "DataMgr.h"
#include "Arms.h"
USING_NS_CC;
class CArmsLayer : public Node
{
public:
	CArmsLayer();
	~CArmsLayer();
	virtual bool init();
	void createArms(int nID,Vec2 pos);
	CArms* isHaveArms(Vec2 tiledPos);
	CREATE_FUNC(CArmsLayer);
private:

};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
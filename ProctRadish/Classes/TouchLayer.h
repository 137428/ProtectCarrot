#ifndef __TOUCHLAYER_H__
#define __TOUCHLAYER_H__
#include "cocos2d.h"
USING_NS_CC;
class CTouchLayer : public Node
{
public:
	CTouchLayer();
	~CTouchLayer();
	virtual bool init();
	CREATE_FUNC(CTouchLayer);
private:
	void addTouch();
};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
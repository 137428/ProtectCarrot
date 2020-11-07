#ifndef __UPCARDLAYER_H__
#define __UPCARDLAYER_H__
#include "cocos2d.h"
#include "Arms.h"
USING_NS_CC;
class CUpCardLayer : public Node
{
public:
	CUpCardLayer();
	~CUpCardLayer();
	virtual bool init();
	void clickEvent(Vec2 clickPos, CArms* pArms);
	void setSpriteCard(CArms* pArms);
	CREATE_FUNC(CUpCardLayer);
private:
	Sprite* m_pUpGrade;
	Sprite* m_pSell;
	Sprite* m_pRander;
	CArms* m_pSelect;
};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
#ifndef __CARDLAYER_H__
#define __CARDLAYER_H__
#include "cocos2d.h"
#include "Card.h"
USING_NS_CC;
class CCardLayer : public Node
{
public:
	CCardLayer();
	~CCardLayer();
	virtual bool init();
	void createCard();
	void clickEvent(Vec2 clickPos);
	void setCardSprite(int nMoney);
	CCard* clickCard(Vec2 clickPos);
	CREATE_FUNC(CCardLayer);
private:
	Sprite* m_pCardColony;
	std::vector<CCard*> m_vecCard;
};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
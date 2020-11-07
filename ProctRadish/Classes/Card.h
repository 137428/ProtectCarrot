#ifndef __CARD_H__
#define __CARD_H__
#include "cocos2d.h"
#include "DataClass.h"
USING_NS_CC;
class CCard : public Sprite
{
public:
	CCard();
	~CCard();
	virtual bool initWithData(SCardDt* pCard);
	static CCard* createWithData(SCardDt* pCard);
	void setSprite(int nMoney);
	CC_SYNTHESIZE(int, m_nArmsID, ArmsID);
	CC_SYNTHESIZE(int, m_nMoney, Money);
private:
	string m_strName;
};
#endif
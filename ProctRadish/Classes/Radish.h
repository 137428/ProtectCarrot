#ifndef __RADISH_H__
#define __RADISH_H__
#include "cocos2d.h"
USING_NS_CC;
class CRadish : public Node
{
public:
	CRadish();
	~CRadish();
	virtual bool init();
	bool Damage();
	void clickEvent(Vec2 clickPos);
	CREATE_FUNC(CRadish);
	CC_SYNTHESIZE(int ,m_nHP,Hp);
private:
	Sprite* m_pHp;
	Sprite* m_pModel;
};
#endif
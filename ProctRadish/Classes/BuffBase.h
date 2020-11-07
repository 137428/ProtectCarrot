#ifndef __BUFFBASE_H__
#define __BUFFBASE_H__
#include "cocos2d.h"
#include "DataClass.h"
USING_NS_CC;

struct SData 
{
	float fTime;
	int nValue;
	Sprite* pSprite;
};
class CBuffBase : public Node
{
public:
	CBuffBase();
	~CBuffBase();
	virtual bool init();
	void addBuffNode(Node* pNode, SBuffDt* pBuff);
	void removeBuffNode(Node* pNode);
	virtual void update(float delta);
protected:
	std::map<Node*, SData*> m_mapBuff;
};


#endif
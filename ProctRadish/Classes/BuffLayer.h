#ifndef __BUFFLAYER_H__
#define __BUFFLAYER_H__
#include "cocos2d.h"
#include "DataClass.h"
#include "DataMgr.h"
#include "BuffBase.h"

USING_NS_CC;
class CBuffLayer : public Node
{
public:
	CBuffLayer();
	~CBuffLayer();
	virtual bool init();
	void inintCallBack();
	virtual void update(float delta);
	void addBuff(Node* pNode,int nBuffID);
	void removeBuff(Node* pNode);
	CREATE_FUNC(CBuffLayer);
private:
	std::map<int, CBuffBase*>m_mapCallBack;
};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
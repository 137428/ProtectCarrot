#include "BuffLayer.h"
#include "Buff.h"
CBuffLayer::CBuffLayer()
{

}

CBuffLayer::~CBuffLayer()
{

}

bool CBuffLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->inintCallBack();
	this->scheduleUpdate();
	return true;
}


void CBuffLayer::inintCallBack()
{
	m_mapCallBack[7001] =CBuffSpeed::create();
	m_mapCallBack[7001]->retain();
	m_mapCallBack[7002] = CBuffHurt::create();
	m_mapCallBack[7002]->retain();
}

void CBuffLayer::addBuff(Node* pNode, int nBuffID)
{
	if (nBuffID==0)
	{
		return;
	}
	CBuffDtMgr* pBuffMgr=static_cast<CBuffDtMgr*>(CDataMgr::getInstance()->getData("BuffMgr"));
	SBuffDt* pBuffDt = static_cast<SBuffDt*>(pBuffMgr->getDataByID(nBuffID));
	m_mapCallBack[nBuffID]->addBuffNode(pNode, pBuffDt);
}

void CBuffLayer::update(float delta)
{
	m_mapCallBack[7001]->update(delta);
	m_mapCallBack[7002]->update(delta);
}

void CBuffLayer::removeBuff(Node* pNode)
{
	m_mapCallBack[7001]->removeBuffNode(pNode);
	m_mapCallBack[7002]->removeBuffNode(pNode);
}


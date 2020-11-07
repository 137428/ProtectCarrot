#include "BulletLayer.h"
#include "Bullet.h"
#include "GameScene.h"
CBulletLayer::CBulletLayer()
{

}

CBulletLayer::~CBulletLayer()
{

}

bool CBulletLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->inintCallBack();
	return true;
}

CBulletBase* CBulletLayer::addBullet(int nID, Vec2 pos, Node* pNode, float fAckRange, int nGrade)
{
	CArms* pArms=static_cast<CArms*>(pNode);
	CBulletDtMgr* pBulletDtMgr = static_cast<CBulletDtMgr*>(CDataMgr::getInstance()->getData("BulletMgr"));//拿到子弹数据管理者
	SBulletDt* pBulletDt = static_cast<SBulletDt*>(pBulletDtMgr->getDataByID(nID));
	CBulletBase* pBullet = m_mapCallBack[pBulletDt->strType](pBulletDt, nGrade);
	pBullet->setPosition(pos);
	pBullet->setAckRange(fAckRange);
	Vec2 Dir = (pNode->getPosition() - pos).getNormalized();
	pBullet->setDir(Dir);

	float fAngel = Dir.getAngle(Vec2(0,1));
	pBullet->setRotation(CC_RADIANS_TO_DEGREES(fAngel));

	if ("Static"==pBulletDt->strType)
	{
		pBullet->update(0.1f);
		Animate* pAnimate=CGameScene::getInstance()->getAnimateLayer()->getAnimate(pBulletDt->nMoveAnimateID + nGrade - 1);//添加动画
		CallFunc* pCall = CallFunc::create([=](){
			pBullet->removeFromParent();
		});
		pBullet->runAction(Sequence::createWithTwoActions(pAnimate, pCall));
	}
	else
	{
		CGameScene::getInstance()->getAnimateLayer()->changeAction(pBullet, pBulletDt->nMoveAnimateID + nGrade - 1, true, 0.2f);//添加动画
	}

	this->addChild(pBullet);
	return pBullet;
}

void CBulletLayer::inintCallBack()
{
	m_mapCallBack["Common"] = [&](SBulletDt* pBulletDt, int nGrand){
		return CBulletCommon::createWithData(pBulletDt, nGrand);
	};
	m_mapCallBack["Through"] = [&](SBulletDt* pBulletDt, int nGrand){
		return CBulletThrough::createWithData(pBulletDt, nGrand);
	};
	m_mapCallBack["Radial"] = [&](SBulletDt* pBulletDt, int nGrand){
		return CBulletRadial::createWithData(pBulletDt, nGrand);
	};
	m_mapCallBack["Static"] = [&](SBulletDt* pBulletDt, int nGrand){
		return CBulletStatic::createWithData(pBulletDt, nGrand);
	};
}


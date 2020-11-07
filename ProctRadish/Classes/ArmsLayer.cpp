#include "ArmsLayer.h"
#include "GameScene.h"
CArmsLayer::CArmsLayer()
{

}

CArmsLayer::~CArmsLayer()
{

}

bool CArmsLayer::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

void CArmsLayer::createArms(int nID,Vec2 pos)
{
	Vec2 tiledPos = CGameScene::getInstance()->getGameMap()->getTiledByPos(pos);
	if (this->isHaveArms(tiledPos))
	{
		return;
	}
	Vec2 centerPos = CGameScene::getInstance()->getGameMap()->getPixelByTiledPos(tiledPos);

	CArmsDtMgr* pArmsDtMgr=static_cast<CArmsDtMgr*>(CDataMgr::getInstance()->getData("ArmsMgr"));
	SArmsDt* pArmsDt = static_cast<SArmsDt*>(pArmsDtMgr->getDataByID(nID));
	CArms* pArms = CArms::createWithData(pArmsDt);
	pArms->setPosition(centerPos);
	this->addChild(pArms);
	CGameScene::getInstance()->getUILayer()->addMoney(-pArmsDt->vecMoney[0]);//¿Û³ý½ð±Ò
}

CArms* CArmsLayer::isHaveArms(Vec2 tiledPos)
{
	Vector<Node*> vecNodes = this->getChildren();
	for (Node* pNode:vecNodes)
	{
		Vec2 nodeTile = CGameScene::getInstance()->getGameMap()->getTiledByPos(pNode->getPosition());
		if (nodeTile==tiledPos)
		{
			return static_cast<CArms*>(pNode);
		}
	}

	return nullptr;
}


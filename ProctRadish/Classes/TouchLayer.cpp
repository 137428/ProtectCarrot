#include "TouchLayer.h"
#include "GameScene.h"
CTouchLayer::CTouchLayer()
{

}

CTouchLayer::~CTouchLayer()
{

}

bool CTouchLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->addTouch();
	return true;
}

void CTouchLayer::addTouch()
{
	EventListenerTouchOneByOne* pListener = EventListenerTouchOneByOne::create();

	pListener->onTouchBegan = [](Touch* pTouch, Event*){
		CGameScene::getInstance()->getRadish()->clickEvent(pTouch->getLocation());
		Vec2 tiledPos = CGameScene::getInstance()->getGameMap()->getTiledByPos(pTouch->getLocation());
		CArms* pArms = CGameScene::getInstance()->getArmsLayer()->isHaveArms(tiledPos);
		if (!CGameScene::getInstance()->getCardLayer()->isVisible() && pArms || CGameScene::getInstance()->getUpCardLayer()->isVisible())
		{
			CGameScene::getInstance()->getCardLayer()->setVisible(false);
			//Éý¼¶
			CGameScene::getInstance()->getUpCardLayer()->clickEvent(pTouch->getLocation(), pArms);
		}
		else
		{
			//´´½¨
			CGameScene::getInstance()->getCardLayer()->clickEvent(pTouch->getLocation());
		}

		return true;
	};


	_eventDispatcher->addEventListenerWithSceneGraphPriority(pListener, this);
}



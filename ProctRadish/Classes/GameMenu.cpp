#include "GameMenu.h"
#include "GameLevel.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
CGameMenu::CGameMenu()
{

}

CGameMenu::~CGameMenu()
{

}

bool CGameMenu::init()
{
	if (!Scene::init())
	{
		return false;
	}
	Node* pMenuNode = CSLoader::createNode("GameMenu.csb");
	this->addChild(pMenuNode);

	ui::Button* pStart = static_cast<ui::Button*>(pMenuNode->getChildByName("MenuStartButton"));

	pStart->addTouchEventListener([=](Ref*, Widget::TouchEventType){
	
		Director::getInstance()->replaceScene(CGameLevel::create());
	});

	return true;
}


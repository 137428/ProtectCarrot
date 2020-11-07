#include "GameLevel.h"
#include "DataMgr.h"
#include "DataClass.h"
#include "GameScene.h"
CGameLevel::CGameLevel()
{

}

CGameLevel::~CGameLevel()
{

}

bool CGameLevel::init()
{
	if (!Scene::init())
	{
		return false;
	}


	Node* pMenuNode = CSLoader::createNode("GameLevel.csb");
	this->addChild(pMenuNode);

	m_pStartButton = static_cast<ui::Button*>(pMenuNode->getChildByName("LevelStartButton"));

	m_pStartButton->addTouchEventListener([=](Ref*, Widget::TouchEventType){
		CLevelDtMgr* pLevelMgr=static_cast<CLevelDtMgr*>(CDataMgr::getInstance()->getData("LevelMgr"));
		pLevelMgr->setCurIndex(m_pPageView->getCurPageIndex());
		CGameScene::deletInstance();
		Director::getInstance()->replaceScene(CGameScene::getInstance());
	//进入游戏主场景
	
	});
	this->addPageView();
	this->createButton();
	return true;
}

void CGameLevel::addPageView()
{
	CLevelDtMgr* pLevelMgr = static_cast<CLevelDtMgr*>(CDataMgr::getInstance()->getData("LevelMgr"));//拿到关卡数据管理者
	m_pPageView = PageView::create();//创建PageView
	Sprite* pSpriteTemp = Sprite::createWithSpriteFrameName(static_cast<SLevelDt*>(pLevelMgr->getDataByID(1001))->strViewImg);
	m_pPageView->setContentSize(WINSIZE);//设置PageView大小
	for (int i = 0; i < pLevelMgr->getsize();i++)//添加Layout
	{
		Layout* pLayout = Layout::create();
		Sprite* pSprite=Sprite::createWithSpriteFrameName(static_cast<SLevelDt*>(pLevelMgr->getDataByID(1001 + i))->strViewImg);
		Sprite* pSpriteCard = Sprite::createWithSpriteFrameName(static_cast<SLevelDt*>(pLevelMgr->getDataByID(1001 + i))->strCardView);
		pLayout->addChild(pSprite);
		pLayout->addChild(pSpriteCard);
		pSprite->setPosition(WINSIZE.width/2,WINSIZE.height/2+50);
		pSpriteCard->setPosition(WINSIZE.width / 2, WINSIZE.height / 2-pSprite->getContentSize().height/2);
		m_pPageView->addPage(pLayout);
	}
	m_pPageView->setTouchEnabled(false);
	this->addChild(m_pPageView);
}



void CGameLevel::createButton()
{
	m_pLeftButton = MenuItemImage::create("Level/LeftNormal.png", "Level/LeftSelect.png",[=](Ref*){
		m_pRightButton->setVisible(true);
		m_pPageView->setCurrentPageIndex(m_pPageView->getCurPageIndex() - 1);
		if (m_pPageView->getCurPageIndex()<=0)
		{
			m_pLeftButton->setVisible(false);
		}
		CLevelDtMgr* pLevelMgr = static_cast<CLevelDtMgr*>(CDataMgr::getInstance()->getData("LevelMgr"));//拿到关卡数据管理者
		if (m_pPageView->getCurPageIndex()<pLevelMgr->getLockLevel())
		{
			m_pStartButton->setEnabled(true);
		}
	});
	m_pLeftButton->setVisible(false);
	m_pRightButton = MenuItemImage::create("Level/RightNormal.png", "Level/RightSelect.png", [=](Ref*){
		m_pLeftButton->setVisible(true);
		m_pPageView->setCurrentPageIndex(m_pPageView->getCurPageIndex() + 1);
		int nCount = m_pPageView->getChildrenCount();
		if (m_pPageView->getCurPageIndex() >= nCount-1)
		{
			m_pRightButton->setVisible(false);
		}
		CLevelDtMgr* pLevelMgr = static_cast<CLevelDtMgr*>(CDataMgr::getInstance()->getData("LevelMgr"));//拿到关卡数据管理者
		if (m_pPageView->getCurPageIndex() >= pLevelMgr->getLockLevel())
		{
			m_pStartButton->setEnabled(false);
		}
		
	});
	m_pLeftButton->setPosition(80, WINSIZE.height / 2);
	m_pRightButton->setPosition(WINSIZE.width - 80, WINSIZE.height / 2);
	Menu* pMenu = Menu::create(m_pLeftButton, m_pRightButton, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu);
}

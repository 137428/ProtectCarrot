#include "UILayer.h"
#include "DataClass.h"
#include "DataMgr.h"
#include "GameScene.h"
#include "GameLevel.h"
CUILayer::CUILayer()
{

}

CUILayer::~CUILayer()
{

}

bool CUILayer::init()
{
	if (!Node::init())
	{
		return false;
	}

	CLevelDtMgr* pLevelDtMgr = static_cast<CLevelDtMgr*>(CDataMgr::getInstance()->getData("LevelMgr"));//�õ��ؿ����ݹ�����
	SLevelDt* pLevelDt = pLevelDtMgr->getCurData();

	m_nMoney = pLevelDt->nStartMoney;

	Sprite* pBg = Sprite::createWithSpriteFrameName("MenuBG.png"); //�˵�����
	pBg->setPosition(WINSIZE.width / 2, WINSIZE.height - pBg->getContentSize().height / 2);
	this->addChild(pBg);

	m_pMoney = LabelAtlas::create(StringUtils::format("%d", m_nMoney), "font/numwhite-hd.png", 20, 32, '.');//���
	m_pMoney->setPosition(100, WINSIZE.height - pBg->getContentSize().height / 2);
	this->addChild(m_pMoney);

	//��ͣ��ť
	MenuItemImage* pPause = MenuItemImage::create();
	SpriteFrame* pPauseNormalFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("pause01.png");
	pPause->setNormalSpriteFrame(pPauseNormalFrame);
	SpriteFrame* pPauseSelectFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("pause02.png");
	pPause->setSelectedSpriteFrame(pPauseSelectFrame);

	//�ָ���ť
	MenuItemImage* pResum = MenuItemImage::create();
	SpriteFrame* pResumNormalFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("pause11.png");
	pResum->setNormalSpriteFrame(pResumNormalFrame);
	SpriteFrame* pResumSelectFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("pause12.png");
	pResum->setSelectedSpriteFrame(pResumSelectFrame);

	m_pPauseResum = MenuItemToggle::createWithCallback([=](Ref* pRef){
		if (0 == static_cast<MenuItemToggle*>(pRef)->getSelectedIndex())
		{
			m_pPause->setVisible(false);
			m_pWave->setVisible(true);
			Director::getInstance()->resume();
		}
		else if (1 == static_cast<MenuItemToggle*>(pRef)->getSelectedIndex())
		{
			m_pPause->setVisible(true);
			m_pWave->setVisible(false);
			Director::getInstance()->pause();
		}
	}, pPause, pResum, NULL);
	m_pPauseResum->setPosition(800, WINSIZE.height - pBg->getContentSize().height / 2);

	//�����ٶȰ�ť
	MenuItemImage* pSpeed = MenuItemImage::create();
	SpriteFrame* pSpeedNormalFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("speed11.png");
	pSpeed->setNormalSpriteFrame(pSpeedNormalFrame);
	SpriteFrame* pSpeedSelectFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("speed12.png");
	pSpeed->setSelectedSpriteFrame(pSpeedSelectFrame);

	//���ٰ�ť
	MenuItemImage* pTwoSpeed = MenuItemImage::create();
	SpriteFrame* pTwoSpeedNormalFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("speed21.png");
	pTwoSpeed->setNormalSpriteFrame(pTwoSpeedNormalFrame);
	SpriteFrame* pTwoSpeedSelectFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("speed22.png");
	pTwoSpeed->setSelectedSpriteFrame(pTwoSpeedSelectFrame);

	MenuItemToggle* pAddSpeed = MenuItemToggle::createWithCallback([=](Ref* pRef){
		if (0 == static_cast<MenuItemToggle*>(pRef)->getSelectedIndex())
		{
			Director::getInstance()->getScheduler()->setTimeScale(1.0f);
		}
		else if (1 == static_cast<MenuItemToggle*>(pRef)->getSelectedIndex())
		{
			Director::getInstance()->getScheduler()->setTimeScale(2.0f);
		}
	}, pSpeed, pTwoSpeed, NULL);
	pAddSpeed->setPosition(700, WINSIZE.height - pBg->getContentSize().height / 2);


	//�˵���ť
	MenuItemImage* pMenuButton = MenuItemImage::create("", "", [=](Ref*){
		m_pPauseResum->setSelectedIndex(1);
		m_pPauseResum->setEnabled(false);
		m_pMenu->setVisible(true);
		Director::getInstance()->pause();
	});
	SpriteFrame* pMenuButtonNormalFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("menu01.png");
	pMenuButton->setNormalSpriteFrame(pMenuButtonNormalFrame);
	SpriteFrame* pMenuButtonSelectFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("menu02.png");
	pMenuButton->setSelectedSpriteFrame(pMenuButtonSelectFrame);
	pMenuButton->setPosition(900, WINSIZE.height - pBg->getContentSize().height / 2);

	Menu* pMenu = Menu::create(m_pPauseResum, pAddSpeed,pMenuButton, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu);

	//�˵�
	m_pMenu = Sprite::createWithSpriteFrameName("menu_bg.png");
	m_pMenu->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	m_pMenu->setVisible(false);
	this->addChild(m_pMenu,1);

	//������Ϸ��ť
	MenuItemImage* pResumButton = MenuItemImage::create("", "", [=](Ref*){
		m_pPauseResum->setSelectedIndex(0);
		m_pPauseResum->setEnabled(true);
		Director::getInstance()->resume();
		m_pMenu->setVisible(false);
	});
	SpriteFrame* pResumButtonNormalFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_resume_normal_CN.png");
	pResumButton->setNormalSpriteFrame(pResumButtonNormalFrame);
	SpriteFrame* pResumButtonSelectFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_resume_pressed_CN.png");
	pResumButton->setSelectedSpriteFrame(pResumButtonSelectFrame);
	pResumButton->setPosition(240,276);

	//���¿�ʼ��Ϸ��ť
	MenuItemImage* pRestartButton = MenuItemImage::create("", "", [=](Ref*){
		Director::getInstance()->resume();
		m_pMenu->setVisible(false);
		CGameScene::deletInstance();
		Director::getInstance()->getScheduler()->setTimeScale(1.0f);
		Director::getInstance()->replaceScene(CGameScene::getInstance());
	});
	SpriteFrame* pRestartButtonNormalFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_restart_normal_CN.png");
	pRestartButton->setNormalSpriteFrame(pRestartButtonNormalFrame);
	SpriteFrame* pRestartButtonSelectFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_restart_pressed_CN.png");
	pRestartButton->setSelectedSpriteFrame(pRestartButtonSelectFrame);
	pRestartButton->setPosition(240, 182);

	//ѡ��ؿ���ť
	MenuItemImage* pQuitButton = MenuItemImage::create("", "", [=](Ref*){
		Director::getInstance()->resume();
		m_pMenu->setVisible(false);
		CGameScene::deletInstance();
		Director::getInstance()->getScheduler()->setTimeScale(1.0f);
		Director::getInstance()->replaceScene(CGameLevel::create());
	});
	SpriteFrame* pQuitButtonNormalFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_quit_normal_CN.png");
	pQuitButton->setNormalSpriteFrame(pQuitButtonNormalFrame);
	SpriteFrame* pQuitButtonSelectFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_quit_pressed_CN.png");
	pQuitButton->setSelectedSpriteFrame(pQuitButtonSelectFrame);
	pQuitButton->setPosition(240, 88);

	Menu* pMenu1 = Menu::create(pResumButton, pRestartButton, pQuitButton, NULL);
	pMenu1->setPosition(Vec2::ZERO);
	m_pMenu->addChild(pMenu1);

	//����
	m_pWave = Node::create();
	Sprite* pWave = Sprite::createWithSpriteFrameName("MenuCenter_01_CN.png");
	m_pWave->setPosition(400, WINSIZE.height - pBg->getContentSize().height / 2);
	m_pWave->addChild(pWave);

	m_pMaxWave = LabelAtlas::create(StringUtils::format("%d", pLevelDt->vecWave.size()), "font/numwhite-hd.png", 20, 32, '.');//�ܲ���
	m_pWave->addChild(m_pMaxWave);

	m_pCurWaveLow = LabelAtlas::create("1", "font/numwhite-hd.png", 20, 32, '.');//��ǰ������λ
	m_pCurWaveLow->setPosition(-65, 0);
	m_pWave->addChild(m_pCurWaveLow);

	m_pCurWaveHigh = LabelAtlas::create("0", "font/numwhite-hd.png", 20, 32, '.');//��ǰ����ʮλ
	m_pCurWaveHigh->setPosition(-113, 0);
	m_pWave->addChild(m_pCurWaveHigh);
	this->addChild(m_pWave);

	//��ͣ��
	m_pPause = Sprite::createWithSpriteFrameName("MenuCenter_02_CN.png");
	m_pPause->setPosition(400, WINSIZE.height - pBg->getContentSize().height / 2);
	m_pPause->setVisible(false);
	this->addChild(m_pPause);

	//����ʱ
	m_nTime = 1;
	m_pTime = Node::create();
	m_pTime->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	Sprite* pCountDownBg = Sprite::createWithSpriteFrameName("countdown_11.png");//����ͼ
	m_pCountDown = Sprite::createWithSpriteFrameName("countdown_12.png");//��תͼ
	m_pTimeNumber = Sprite::createWithSpriteFrameName("countdown_01.png");//����
	m_pTime->addChild(pCountDownBg);
	m_pTime->addChild(m_pCountDown);
	m_pTime->addChild(m_pTimeNumber);

	RotateBy* pRotateBy = RotateBy::create(1.0f, -360);//��ת����

	CallFunc* pCall = CallFunc::create([&](){
		if (m_nTime>=3)
		{
			return;
		}
		m_nTime++;
		m_pTimeNumber->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("countdown_%02d.png", m_nTime)));//ÿ��1���޸�ͼƬ
	});

	Sequence* pSeq = Sequence::createWithTwoActions(pRotateBy, pCall);

	CallFunc* pCallGo = CallFunc::create([&](){
		m_pCountDown->stopAllActions();
		m_pCountDown->removeFromParent();
		m_pTimeNumber->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("countdown_13.png"));
		m_pTimeNumber->setScale(0.5f);
		ScaleTo* pScaleto = ScaleTo::create(1.0f, 1.5f);
		ScaleTo* pScaleto1 = ScaleTo::create(1.0f, 1.0f);
		RotateBy* pRotateBy = RotateBy::create(1.0f, 360);
		RotateBy* pRotateBy1 = RotateBy::create(1.0f, -360);
		Sequence* pSeqScale = Sequence::createWithTwoActions(pScaleto, pScaleto1);

		CallFunc* pCallEnd = CallFunc::create([=](){
			m_pTimeNumber->stopAllActions();
			m_pTime->removeFromParent();
			CGameScene::getInstance()->getMonsterLayer()->startCreatMonster();
		});

		Sequence* pSeqRotate = Sequence::create(pRotateBy, pRotateBy1,pCallEnd,NULL);
		m_pTimeNumber->runAction(pSeqScale);
		m_pTimeNumber->runAction(pSeqRotate);
	});

	m_pCountDown->runAction(Sequence::createWithTwoActions(Repeat::create(pSeq, 3), pCallGo));

	this->addChild(m_pTime);

	return true;
}

void CUILayer::addMoney(int nMoney)
{
	m_nMoney += nMoney;
	m_pMoney->setString(StringUtils::format("%d", m_nMoney));
}

void CUILayer::setCurWave(int nCurWave)
{
	m_pCurWaveLow->setString(StringUtils::format("%d", nCurWave % 10));
	m_pCurWaveHigh->setString(StringUtils::format("%d", nCurWave / 10));
}

void CUILayer::createOver(int nCurWave, int nMaxWave,bool bWin)
{

	Sprite* pOver;

	//ѡ��ؿ���ť
	MenuItemImage* pQuitButton = MenuItemImage::create("", "", [=](Ref*){
		Director::getInstance()->resume();
		CGameScene::deletInstance();
		Director::getInstance()->getScheduler()->setTimeScale(1.0f);
		Director::getInstance()->replaceScene(CGameLevel::create());
	});
	SpriteFrame* pQuitButtonNormalFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("select_normal_CN.png");
	pQuitButton->setNormalSpriteFrame(pQuitButtonNormalFrame);
	SpriteFrame* pQuitButtonSelectFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("select_pressed_CN.png");
	pQuitButton->setSelectedSpriteFrame(pQuitButtonSelectFrame);
	pQuitButton->setPosition(500, 140);

	if (bWin)
	{
		//�޸�Ϊ��һ��
		CLevelDtMgr* pLevelMgr = static_cast<CLevelDtMgr*>(CDataMgr::getInstance()->getData("LevelMgr"));
		pLevelMgr->addLockLevel();
		//ʤ��
		pOver = Sprite::createWithSpriteFrameName("win_bg.png");
		//������Ϸ��ť
		MenuItemImage* pRestartButton = MenuItemImage::create("", "", [=](Ref*){
			Director::getInstance()->resume();
			CGameScene::deletInstance();
			Director::getInstance()->getScheduler()->setTimeScale(1.0f);
			pLevelMgr->addCurIndex();
			TransitionJumpZoom* pTran = TransitionJumpZoom::create(1.0f, CGameScene::getInstance());
			Director::getInstance()->replaceScene(pTran);
		});
		SpriteFrame* pRestartButtonNormalFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("continue_normal_CN.png");
		pRestartButton->setNormalSpriteFrame(pRestartButtonNormalFrame);
		SpriteFrame* pRestartButtonSelectFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("continue_pressed_CN.png");
		pRestartButton->setSelectedSpriteFrame(pRestartButtonSelectFrame);
		pRestartButton->setPosition(240, 140);

		Menu* pMenu = Menu::create(pRestartButton, pQuitButton, NULL);
		pMenu->setPosition(Vec2::ZERO);
		pOver->addChild(pMenu);


	}
	else
	{
		//ʧ��
		pOver = Sprite::createWithSpriteFrameName("lose_bg.png");

		//���¿�ʼ��ť
		MenuItemImage* pRestartButton = MenuItemImage::create("", "", [=](Ref*){
			Director::getInstance()->resume();
			CGameScene::deletInstance();
			Director::getInstance()->getScheduler()->setTimeScale(1.0f);
			Director::getInstance()->replaceScene(CGameScene::getInstance());
		});
		SpriteFrame* pRestartButtonNormalFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("retry_normal_CN.png");
		pRestartButton->setNormalSpriteFrame(pRestartButtonNormalFrame);
		SpriteFrame* pRestartButtonSelectFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("retry_pressed_CN.png");
		pRestartButton->setSelectedSpriteFrame(pRestartButtonSelectFrame);
		pRestartButton->setPosition(240, 140);
		Menu* pMenu = Menu::create(pRestartButton, pQuitButton, NULL);
		pMenu->setPosition(Vec2::ZERO);
		pOver->addChild(pMenu);
	}

	//������ʾ
	Sprite* pWaveImg = Sprite::createWithSpriteFrameName("lose_bg_CN.png");
	pWaveImg->setPosition(385, 240);

	LabelAtlas* pCurWaveLow = LabelAtlas::create(StringUtils::format("%d", nCurWave % 10), "font/numwhite-hd.png", 20, 32, '.');//��ǰ������λ
	pCurWaveLow->setPosition(390, 255);
	pOver->addChild(pCurWaveLow);

	LabelAtlas* pCurWaveHigh = LabelAtlas::create(StringUtils::format("%d", nCurWave/10), "font/numwhite-hd.png", 20, 32, '.');//��ǰ����ʮλ
	pCurWaveHigh->setPosition(345, 255);
	pOver->addChild(pCurWaveHigh);

	LabelAtlas* pMaxWave = LabelAtlas::create(StringUtils::format("%d", nMaxWave), "font/numwhite-hd.png", 20, 32, '.');//�����
	pMaxWave->setPosition(460, 255);
	pOver->addChild(pMaxWave);

	int nCurLevel = static_cast<CLevelDtMgr*>(CDataMgr::getInstance()->getData("LevelMgr"))->getCurIndex() + 1;
	LabelAtlas* pCurLevel = LabelAtlas::create(StringUtils::format("%d", nCurLevel), "font/numwhite-hd.png", 20, 32, '.');//��ǰ�ؿ�
	pCurLevel->setPosition(320, 195);
	pOver->addChild(pCurLevel);

	pOver->addChild(pWaveImg);

	//�˵�
	pOver->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	EventListenerTouchOneByOne* pLister = EventListenerTouchOneByOne::create();
	pLister->setSwallowTouches(true);
	pLister->onTouchBegan = [=](Touch*, Event*){
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pLister, pOver);
	this->addChild(pOver);

	Director::getInstance()->pause();
}


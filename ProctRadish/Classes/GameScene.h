#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include "cocos2d.h"
#include "GameMap.h"
#include "MonsterLayer.h"
#include "CardLayer.h"
#include "ArmsLayer.h"
#include "BulletLayer.h"
#include "BuffLayer.h"
#include "UpCardLayer.h"
#include "Radish.h"
#include "UILayer.h"
#include "AnimateLayer.h"
USING_NS_CC;
class CGameScene : public Scene
{
public:
	~CGameScene();
	virtual bool init();
	CREATE_FUNC(CGameScene);
	static CGameScene* getInstance();
	static void deletInstance();
	void update(float delta);
	CC_SYNTHESIZE(CGameMap*,m_pGameMap,GameMap);
	CC_SYNTHESIZE(CMonsterLayer*, m_pMonsterLayer, MonsterLayer);
	CC_SYNTHESIZE(CAnimateLayer*, m_pAnimateLayer, AnimateLayer);
	CC_SYNTHESIZE(CCardLayer*, m_pCardLayer, CardLayer);
	CC_SYNTHESIZE(CArmsLayer*, m_pArmsLayer, ArmsLayer);
	CC_SYNTHESIZE(CBulletLayer*, m_pBulletLayer, BulletLayer);
	CC_SYNTHESIZE(CBuffLayer*, m_pBuffLayer, BuffLayer);
	CC_SYNTHESIZE(CUpCardLayer*, m_pUpCardLayer, UpCardLayer);
	CC_SYNTHESIZE(CRadish*, m_pRadish, Radish);
	CC_SYNTHESIZE(int,m_nMoney,Money);
	CC_SYNTHESIZE(CUILayer*, m_pUILayer, UILayer);
private:
	CGameScene();
	static CGameScene* m_spInstance;
};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
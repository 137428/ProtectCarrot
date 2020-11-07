#include "LoadData.h"
#include "DataClass.h"
#include "DataMgr.h"
CLoadData::CLoadData()
{

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/stages_theme1-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/PetsTheme01-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/ui_Monster.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/TBottle-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/TFan-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/TFireBottle-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/Items00-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/Items02-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/Items01-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/gamemenu-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/gameover0-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/gameover-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/TSun-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Plist/TSnow-hd.plist");

	CLevelDtMgr* pLevelDtMgr = new CLevelDtMgr();
	pLevelDtMgr->LoadFile("data/LevelDt.json");
	CDataMgr::getInstance()->addData("LevelMgr", pLevelDtMgr);

	CMonsterDtMgr* pMonsterDtMgr = new CMonsterDtMgr();
	pMonsterDtMgr->LoadFile("data/MonsterDt.json");
	CDataMgr::getInstance()->addData("MonsterMgr", pMonsterDtMgr);

	CCardDtMgr* pCardDtMgr = new CCardDtMgr();
	pCardDtMgr->LoadFile("data/CardDt.json");
	CDataMgr::getInstance()->addData("CardMgr", pCardDtMgr);

	CArmsDtMgr* pArmsDtMgr = new CArmsDtMgr();
	pArmsDtMgr->LoadFile("data/ArmsDt.json");
	CDataMgr::getInstance()->addData("ArmsMgr", pArmsDtMgr);

	CBulletDtMgr* pBulletDtMgr = new CBulletDtMgr();
	pBulletDtMgr->LoadFile("data/BulletDt.json");
	CDataMgr::getInstance()->addData("BulletMgr", pBulletDtMgr);

	CBuffDtMgr* pBuffDtMgr = new CBuffDtMgr();
	pBuffDtMgr->LoadFile("data/BuffDt.json");
	CDataMgr::getInstance()->addData("BuffMgr", pBuffDtMgr);

	CAnimateDtMgr* pAnimateDtMgr = new CAnimateDtMgr();
	pAnimateDtMgr->LoadFile("data/AnimateDt.json");
	CDataMgr::getInstance()->addData("AnimateMgr", pAnimateDtMgr);
}

CLoadData::~CLoadData()
{

}


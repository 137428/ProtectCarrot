#include "MonsterLayer.h"
#include "GameScene.h"
#include "DataMgr.h"
CMonsterLayer::CMonsterLayer()
{

}

CMonsterLayer::~CMonsterLayer()
{

}

bool CMonsterLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	CLevelDtMgr* pLevelDtMgr = static_cast<CLevelDtMgr*>(CDataMgr::getInstance()->getData("LevelMgr"));//拿到关卡数据管理者
	m_vecWave = pLevelDtMgr->getCurData()->vecWave;
	m_nCurMonsterCount = 0;
	m_nCurWave = 0;
	m_vecMonsterID = pLevelDtMgr->getCurData()->MonsterID;
	m_nCurWaveMonsterID = rand() % m_vecMonsterID.size() + 2001;

	this->scheduleUpdate();

	return true;
}

void CMonsterLayer::createMonster()
{
	CMonsterDtMgr* pMonsterDtMgr = static_cast<CMonsterDtMgr*>(CDataMgr::getInstance()->getData("MonsterMgr"));//拿到敌人数据管理者	
	SMonsterDt* pMonsterDt = static_cast<SMonsterDt*>(pMonsterDtMgr->getDataByID(m_nCurWaveMonsterID));
	CMonster* pMonster = CMonster::createWithData(pMonsterDt);
	this->addChild(pMonster);
	m_nCurMonsterCount++;
	if (m_nCurMonsterCount>=m_vecWave[m_nCurWave])
	{
		this->unschedule("Monster");
		m_nCurMonsterCount = 0;
		m_nCurWave++;
		m_nCurWaveMonsterID = rand() % m_vecMonsterID.size() + 2001;
	}
}

CMonster* CMonsterLayer::getMonster(float fAckRandge, Vec2 Pos)
{
	Vector<Node*> vecNode = this->getChildren();
	for (Node* pNode : vecNode)
	{
		Vec2 deltaPos = pNode->getPosition() - Pos;
		if (deltaPos.getLength() < fAckRandge)
		{
			return static_cast<CMonster*>(pNode);
		}
	}
	return nullptr;
}

void CMonsterLayer::update(float delta)
{
	if (this->getChildrenCount()<=0&&m_nCurWave<m_vecWave.size()&&!this->isScheduled("Monster")&&m_nCurWave!=0)
	{
		CGameScene::getInstance()->getUILayer()->setCurWave(m_nCurWave + 1);
		this->schedule([=](float){
			this->createMonster();
		}, 1.0f, "Monster");
	}

	if (this->getChildrenCount() <= 0 && m_nCurWave>=m_vecWave.size())
	{
		CGameScene::getInstance()->getUILayer()->createOver(m_nCurWave, m_vecWave.size(),true);
	}
}

void CMonsterLayer::startCreatMonster()
{
	this->createMonster();
	m_nCurMonsterCount++;
	this->schedule([=](float){
		this->createMonster();
	}, 1.0f, "Monster");
}

void CMonsterLayer::GameOver()
{
	CGameScene::getInstance()->getUILayer()->createOver(m_nCurWave, m_vecWave.size(),false);
}

vector<CMonster*> CMonsterLayer::getMonsterVec(float fAckRandge, Vec2 Pos)
{
	Vector<Node*> vecNode = this->getChildren();
	vector<CMonster*> vecMonster;
	for (Node* pNode : vecNode)
	{
		Vec2 deltaPos = pNode->getPosition() - Pos;
		if (deltaPos.getLength() <=fAckRandge)
		{
			vecMonster.push_back(static_cast<CMonster*>(pNode));
		}
	}
	return vecMonster;
}

#ifndef __MONSTERLAYER_H__
#define __MONSTERLAYER_H__
#include "cocos2d.h"
#include "Monster.h"
USING_NS_CC;
class CMonsterLayer : public Node
{
public:
	CMonsterLayer();
	~CMonsterLayer();
	virtual bool init();
	virtual void update(float delta);
	void createMonster();
	void startCreatMonster();
	void GameOver();
	CMonster* getMonster(float fAckRandge,Vec2 Pos);
	vector<CMonster*> getMonsterVec(float fAckRandge, Vec2 Pos);
	CREATE_FUNC(CMonsterLayer);
private:
	std::vector<int> m_vecMonsterID;
	std::vector<int> m_vecWave;
	int m_nCurMonsterCount;
	int m_nCurWave;
	int m_nCurWaveMonsterID;
};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
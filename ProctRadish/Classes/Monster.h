#ifndef __MONSTER_H__
#define __MONSTER_H__
#include "cocos2d.h"
#include "RoleBase.h"
#include "DataClass.h"
USING_NS_CC;
class CMonster : public CRoleBase
{
public:
	CMonster();
	~CMonster();
	static void setPath(vector<Vec2> vecPath);
	virtual bool initWithData(SMonsterDt* pMonster);
	static CMonster* createWithData(SMonsterDt* pMonster);
	void removeMonster();
	virtual void update(float delta);
	bool changeUpdateDir();//改变索引
	void calculateDir();//获取方向
	CC_SYNTHESIZE(float, m_fSpeed, Speed);
	CC_SYNTHESIZE(float, m_fSaveSpeed, SaveSpeed);
private:
	static vector<Vec2> m_vecPath;//路径
	int m_nIndex;
	Vec2 m_vDir;
	bool m_bChangeDir;
	Size m_TiledSize;//格子地图大小
	int m_nMoney;
};
#endif
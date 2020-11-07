#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__
#include "cocos2d.h"
USING_NS_CC;
class CGameMap : public Node
{
public:
	CGameMap();
	~CGameMap();
	virtual bool initWithImgPath(std::string strName);
	static CGameMap* createWithImgPath(std::string strName);

	//转换接口：把像素坐标转换为格子坐标
	Vec2 getTiledByPos(Vec2 pixelPos);
	//转换接口：把格子坐标转换到像素坐标
	Vec2 getPixelByTiledPos(Vec2 tiledPos);
	int clickEvent(Vec2 clickPos);
	//获取设计地图的时候所有的对象的坐标（以后怪物的出生点，拐点坐标）
	std::vector<Vec2> getInitPos();
	//接口，判断一个作标是否在某个层上
	bool isInLayer(std::string strName, Vec2 TiledPos);
	//判断格子是否在地图外
	bool isOutOfMap(Vec2 tiledPos);
	//通过格子坐标获取某个层上使用的某个图快的属性。
	ValueMap getProperty(std::string strName, Vec2 tiledPos);
	//拿到路径最后一个格子像素坐标
	Vec2 getLastTiledPos();
	//拿到第一个格子作标
	Vec2 getFirstTiledPos();
	//格子的大小：像素
	CC_SYNTHESIZE(Size, m_tiledSize, TiledSize);

	CC_SYNTHESIZE(TMXTiledMap*, m_pTiledMap, TiledMap);
private:
	Size m_mapSize;
};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
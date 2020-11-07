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

	//ת���ӿڣ�����������ת��Ϊ��������
	Vec2 getTiledByPos(Vec2 pixelPos);
	//ת���ӿڣ��Ѹ�������ת������������
	Vec2 getPixelByTiledPos(Vec2 tiledPos);
	int clickEvent(Vec2 clickPos);
	//��ȡ��Ƶ�ͼ��ʱ�����еĶ�������꣨�Ժ����ĳ����㣬�յ����꣩
	std::vector<Vec2> getInitPos();
	//�ӿڣ��ж�һ�������Ƿ���ĳ������
	bool isInLayer(std::string strName, Vec2 TiledPos);
	//�жϸ����Ƿ��ڵ�ͼ��
	bool isOutOfMap(Vec2 tiledPos);
	//ͨ�����������ȡĳ������ʹ�õ�ĳ��ͼ������ԡ�
	ValueMap getProperty(std::string strName, Vec2 tiledPos);
	//�õ�·�����һ��������������
	Vec2 getLastTiledPos();
	//�õ���һ����������
	Vec2 getFirstTiledPos();
	//���ӵĴ�С������
	CC_SYNTHESIZE(Size, m_tiledSize, TiledSize);

	CC_SYNTHESIZE(TMXTiledMap*, m_pTiledMap, TiledMap);
private:
	Size m_mapSize;
};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
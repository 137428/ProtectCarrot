#include "GameMap.h"
CGameMap::CGameMap()
{

}

CGameMap::~CGameMap()
{

}


bool CGameMap::initWithImgPath(std::string strName)
{
	if (!Node::init())
	{
		return false;
	}

	m_pTiledMap = TMXTiledMap::create(strName);//背景
	m_pTiledMap->setAnchorPoint(Vec2::ZERO);
	this->addChild(m_pTiledMap);


	m_tiledSize = m_pTiledMap->getTileSize();
	m_mapSize = m_pTiledMap->getMapSize();

	return true;
}

CGameMap* CGameMap::createWithImgPath(std::string strName)
{
	CGameMap* pRef = new CGameMap();
	if (pRef&&pRef->initWithImgPath(strName))
	{
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

cocos2d::Vec2 CGameMap::getTiledByPos(Vec2 pixelPos)
{
	int fX = pixelPos.x / m_tiledSize.width;

	float fResult = pixelPos.y / m_tiledSize.height;
	
	fResult < 0 ?fResult=fResult-1 : fResult;

	int fY = m_mapSize.height-(int)fResult-1;

	return Vec2(fX,fY);
}

cocos2d::Vec2 CGameMap::getPixelByTiledPos(Vec2 tiledPos)
{
	float fX = tiledPos.x*m_tiledSize.width+m_tiledSize.width/2;
	float fY = (m_mapSize.height - tiledPos.y - 1)*m_tiledSize.height + m_tiledSize.height / 2;

	return Vec2(fX,fY);
}

int CGameMap::clickEvent(Vec2 clickPos)
{
	return 0;
}

std::vector<Vec2> CGameMap::getInitPos()
{
	std::vector<Vec2> VecPos;
	TMXObjectGroup* pObject = m_pTiledMap->getObjectGroup("pathObject");//获取对象组
	ValueVector vObject = pObject->getObjects();

	for (int i = 0; i < vObject.size();i++)
	{
		Value vData = vObject[i];
		ValueMap vMap = vData.asValueMap();
		float fX = vMap["x"].asFloat();
		float fY = vMap["y"].asFloat();
		Vec2 tiledPos = this->getTiledByPos(Vec2(fX, fY));
		VecPos.push_back(this->getPixelByTiledPos(tiledPos));
	}
	return VecPos;
}

bool CGameMap::isInLayer(std::string strName, Vec2 TiledPos)
{
	TMXLayer* pLayer = m_pTiledMap->getLayer(strName);
	int nGID = pLayer->getTileGIDAt(TiledPos);
	if (0==nGID)
	{
		return false;
	}
	return true;
}

bool CGameMap::isOutOfMap(Vec2 tiledPos)
{
	if (tiledPos.x<0
		||tiledPos.y<0
		||tiledPos.x>m_mapSize.width-1
		||tiledPos.y>m_mapSize.height-1)
	{
		return true;
	}
	return false;
}

cocos2d::ValueMap CGameMap::getProperty(std::string strName, Vec2 tiledPos)
{
	TMXLayer* pLayer = m_pTiledMap->getLayer(strName);//获取所在的层
	int nGID = pLayer->getTileGIDAt(tiledPos);//获取GID
	Value vData = m_pTiledMap->getPropertiesForGID(nGID);//获取属性
	if (vData.isNull())
	{
		return ValueMap();
	}
	ValueMap vMap = vData.asValueMap();
	return vMap;

}

cocos2d::Vec2 CGameMap::getLastTiledPos()
{
	return this->getPixelByTiledPos(this->getTiledByPos(this->getInitPos().back()));
}

cocos2d::Vec2 CGameMap::getFirstTiledPos()
{
	return this->getPixelByTiledPos(this->getTiledByPos(this->getInitPos()[0]));
}


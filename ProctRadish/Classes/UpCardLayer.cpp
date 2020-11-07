#include "UpCardLayer.h"
#include "Arms.h"
#include "GameScene.h"
CUpCardLayer::CUpCardLayer()
{

}

CUpCardLayer::~CUpCardLayer()
{

}

bool CUpCardLayer::init()
{
	if (!Node::init())
	{
		return false;
	}
	m_pUpGrade = Sprite::create();
	m_pSell = Sprite::create();
	m_pRander = Sprite::create();
	m_pUpGrade->setAnchorPoint(Vec2(0.5,-0.5));
	m_pSell->setAnchorPoint(Vec2(0.5, 1.5));
	this->addChild(m_pRander);
	this->addChild(m_pUpGrade);
	this->addChild(m_pSell);
	this->setVisible(false);
	return true;
}

void CUpCardLayer::clickEvent(Vec2 clickPos, CArms* pArms)
{
	if (this->isVisible())
	{
		if (m_pUpGrade->getBoundingBox().containsPoint(this->convertToNodeSpace(clickPos)))//升级
		{
			int nMoney = m_pSelect->getArmsDt()->vecMoney[m_pSelect->getGrade()];//拿到升级所需金币
			if (m_pSelect->getGrade()<m_pSelect->getArmsDt()->vecMoney.size()//卡片不是顶级卡片
				&&CGameScene::getInstance()->getUILayer()->getMoney()>=nMoney)//剩余金币必须大于升级所需金币
			{
				
				CGameScene::getInstance()->getUILayer()->addMoney(-nMoney);
				m_pSelect->upgrade();
			}
		}

		if (m_pSell->getBoundingBox().containsPoint(this->convertToNodeSpace(clickPos)))//出售
		{
			int nNum = 0;//武器价值

			for (int i = 0; i < m_pSelect->getGrade(); i++)
			{
				nNum += m_pSelect->getArmsDt()->vecMoney[i];
			}

			CGameScene::getInstance()->getUILayer()->addMoney(nNum*0.8);
			m_pSelect->removeFromParent();
			if (m_pSelect->getLastBullet()&&m_pSelect->getLastBullet()->getTag()==1)
			{
				m_pSelect->getLastBullet()->removeFromParent();
			}
		}

		this->setVisible(false);
		return;
	}
	if (!this->isVisible() || pArms)//第一次点击,显示卡片
	{
		Vec2 tiledPos = CGameScene::getInstance()->getGameMap()->getTiledByPos(clickPos);
		Vec2 Pos = CGameScene::getInstance()->getGameMap()->getPixelByTiledPos(tiledPos);
		this->setPosition(Pos);
		this->setSpriteCard(pArms);
		m_pSelect = pArms;
		this->setVisible(true);
	}
	else
	{
		this->setVisible(false);
	}
}
void CUpCardLayer::setSpriteCard(CArms* pArms){	int nMoney = 0;	if (CGameScene::getInstance()->getUILayer()->getMoney() >= pArms->getArmsDt()->vecMoney[pArms->getGrade()])	{		nMoney = pArms->getArmsDt()->vecMoney[pArms->getGrade()];	}	else	{		nMoney = -pArms->getArmsDt()->vecMoney[pArms->getGrade()];    /*  金币不够显示灰色图片*/	}	string strName = StringUtils::format("upgrade_%d.png", nMoney);	if (pArms->getGrade() >= pArms->getArmsDt()->vecMoney.size())	{		strName = "upgrade_0_CN.png";	}	SpriteFrame* pUpGrade = SpriteFrameCache::getInstance()->getSpriteFrameByName(strName);	m_pUpGrade->setSpriteFrame(pUpGrade);	int nNum = 0;	for (int i = 0; i < pArms->getGrade(); i++)	{		nNum += pArms->getArmsDt()->vecMoney[i];	}	strName = StringUtils::format("sell_%d.png", (int)(nNum*0.8));	SpriteFrame* pSell = SpriteFrameCache::getInstance()->getSpriteFrameByName(strName);	m_pSell->setSpriteFrame(pSell);	SpriteFrame* pRander = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("range_%d.png", pArms->getArmsDt()->vecRange[pArms->getGrade()-1]));	m_pRander->setSpriteFrame(pRander);}

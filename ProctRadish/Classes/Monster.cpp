#include "Monster.h"
#include "GameScene.h"

vector<Vec2> CMonster::m_vecPath;

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

bool CMonster::initWithData(SMonsterDt* pMonster)
{
	if (!CRoleBase::init())
	{
		return false;
	}
	m_nIndex = 0;
	m_TiledSize = CGameScene::getInstance()->getGameMap()->getTiledSize();
	m_fSaveSpeed=m_fSpeed = pMonster->fSpeed;
	m_bChangeDir = false;
	m_nHp = m_nMaxHp = 10000;
	m_nMoney = pMonster->nMoney;
	m_pModel=Sprite::createWithSpriteFrameName(pMonster->strImg);
	CGameScene::getInstance()->getAnimateLayer()->changeAction(m_pModel, pMonster->AnimateID, true, 0.2f);
	this->addChild(m_pModel);
	m_pHpNode->setPosition(0, m_pModel->getContentSize().height / 2);
	this->setPosition(m_vecPath[m_nIndex]);
	this->calculateDir();
	this->scheduleUpdate();
	return true;
}

CMonster* CMonster::createWithData(SMonsterDt* pMonster)
{
	CMonster* pRef = new CMonster();
	if (pRef&&pRef->initWithData(pMonster))
	{
		pRef->autorelease();
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

void CMonster::update(float delta)
{
	if (this->changeUpdateDir())//返回为真，表示怪物出界，移除
	{
		this->scheduleUpdate();
		CGameScene::getInstance()->getRadish()->Damage();
		//添加死亡动画
		CGameScene::getInstance()->getAnimateLayer()->createAnimate(this->getPosition(), 3024);
		this->removeMonster();
		return;
	}

	Vec2 pos = this->getPosition();
	pos.x += delta*m_vDir.x*m_fSpeed;
	pos.y += delta*m_vDir.y*m_fSpeed;
	this->setPosition(pos);

}

bool CMonster::changeUpdateDir()
{
	Vec2 MonsterPos = this->getPosition();//拿到怪物当前坐标
	Vec2 NextPos = Vec2(MonsterPos.x + m_vDir.x*(m_TiledSize.width / 2 + 3), MonsterPos.y + m_vDir.y*(m_TiledSize.height / 2 + 3));//拿到怪物的下一个格子坐标
	Vec2 NextTiled = CGameScene::getInstance()->getGameMap()->getTiledByPos(NextPos);//拿到下一个格子坐标
	Vec2 Tiled = CGameScene::getInstance()->getGameMap()->getTiledByPos(MonsterPos);//拿到怪物的当前格子坐标
	if (NextTiled==Tiled)
	{
		m_bChangeDir = false;
	}
	if (CGameScene::getInstance()->getGameMap()->isOutOfMap(NextTiled))//下一个格子出界
	{
		m_bChangeDir = true;
		m_nIndex++;
		this->calculateDir();
		if (m_nIndex >= m_vecPath.size() - 1)
		{
			return true;
		}
	}
	else if (CGameScene::getInstance()->getGameMap()->isInLayer("path",NextTiled))//下一个格子是路径
	{
		if (!m_bChangeDir)
		{
			ValueMap Vmap = CGameScene::getInstance()->getGameMap()->getProperty("path", Tiled);
			if (Vmap.size() != 0&&Vmap["point"].asBool()&&NextTiled!=Tiled)
			{
				m_bChangeDir = true;
				m_nIndex++;
				this->calculateDir();
				if (m_nIndex >=m_vecPath.size() - 1)
				{
					return true;
				}
			}
		}
	}
	else//下一个格子不是路径
	{
		m_bChangeDir = true;
		m_nIndex++;
		this->calculateDir();
		if (m_nIndex>=m_vecPath.size()-1)
		{
			return true;
		}
	}

	return false;
}

void CMonster::calculateDir()
{
	Vec2 pos = m_vecPath[m_nIndex + 1] - m_vecPath[m_nIndex];
	m_vDir = pos.getNormalized();
}

void CMonster::setPath(vector<Vec2> vecPath)
{
	m_vecPath = vecPath;
}

void CMonster::removeMonster()
{
	//移除Buff
	CGameScene::getInstance()->getBuffLayer()->removeBuff(this);
	//添加金币
	if (m_nIndex >= m_vecPath.size() - 1)
	{
		m_nMoney = 14;
	}
	CGameScene::getInstance()->getUILayer()->addMoney(m_nMoney);
	//添加显示金币精灵

	//添加死亡动画
	CGameScene::getInstance()->getAnimateLayer()->createAnimate(this->getPosition(), 3024);
	
	Sprite* pSprite = Sprite::createWithSpriteFrameName(StringUtils::format("money%d.png",m_nMoney));
	pSprite->setPosition(this->getPosition());
	MoveBy* pMoveBy = MoveBy::create(0.5, Vec2(0, 50));
	pSprite->runAction(Sequence::createWithTwoActions(pMoveBy, RemoveSelf::create()));
	CGameScene::getInstance()->getUILayer()->addChild(pSprite);
	this->removeFromParent();
}

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
	if (this->changeUpdateDir())//����Ϊ�棬��ʾ������磬�Ƴ�
	{
		this->scheduleUpdate();
		CGameScene::getInstance()->getRadish()->Damage();
		//�����������
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
	Vec2 MonsterPos = this->getPosition();//�õ����ﵱǰ����
	Vec2 NextPos = Vec2(MonsterPos.x + m_vDir.x*(m_TiledSize.width / 2 + 3), MonsterPos.y + m_vDir.y*(m_TiledSize.height / 2 + 3));//�õ��������һ����������
	Vec2 NextTiled = CGameScene::getInstance()->getGameMap()->getTiledByPos(NextPos);//�õ���һ����������
	Vec2 Tiled = CGameScene::getInstance()->getGameMap()->getTiledByPos(MonsterPos);//�õ�����ĵ�ǰ��������
	if (NextTiled==Tiled)
	{
		m_bChangeDir = false;
	}
	if (CGameScene::getInstance()->getGameMap()->isOutOfMap(NextTiled))//��һ�����ӳ���
	{
		m_bChangeDir = true;
		m_nIndex++;
		this->calculateDir();
		if (m_nIndex >= m_vecPath.size() - 1)
		{
			return true;
		}
	}
	else if (CGameScene::getInstance()->getGameMap()->isInLayer("path",NextTiled))//��һ��������·��
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
	else//��һ�����Ӳ���·��
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
	//�Ƴ�Buff
	CGameScene::getInstance()->getBuffLayer()->removeBuff(this);
	//��ӽ��
	if (m_nIndex >= m_vecPath.size() - 1)
	{
		m_nMoney = 14;
	}
	CGameScene::getInstance()->getUILayer()->addMoney(m_nMoney);
	//�����ʾ��Ҿ���

	//�����������
	CGameScene::getInstance()->getAnimateLayer()->createAnimate(this->getPosition(), 3024);
	
	Sprite* pSprite = Sprite::createWithSpriteFrameName(StringUtils::format("money%d.png",m_nMoney));
	pSprite->setPosition(this->getPosition());
	MoveBy* pMoveBy = MoveBy::create(0.5, Vec2(0, 50));
	pSprite->runAction(Sequence::createWithTwoActions(pMoveBy, RemoveSelf::create()));
	CGameScene::getInstance()->getUILayer()->addChild(pSprite);
	this->removeFromParent();
}

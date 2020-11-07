#ifndef __UILAYER_H__
#define __UILAYER_H__
#include "cocos2d.h"
USING_NS_CC;
class CUILayer : public Node
{
public:
	CUILayer();
	~CUILayer();
	virtual bool init();
	CREATE_FUNC(CUILayer);
	int getMoney()
	{
		return m_nMoney;
	}
	void createOver(int nCurWave,int nMaxWave,bool bWin);
	void addMoney(int nMoney);
	void setCurWave(int nCurWave);
private:
	int m_nMoney;
	LabelAtlas* m_pMoney;//金币
	Node* m_pWave;//波数挂载节点
	Sprite* m_pPause;//暂停中
	LabelAtlas* m_pMaxWave;//总波数
	LabelAtlas* m_pCurWaveLow;//当前波数个位
	LabelAtlas* m_pCurWaveHigh;//当前波数十位
	Node* m_pTime;
	Sprite* m_pTimeNumber;
	int m_nTime;
	Sprite* m_pCountDown;
	Sprite* m_pMenu;
	MenuItemToggle* m_pPauseResum;//暂停恢复按钮
};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
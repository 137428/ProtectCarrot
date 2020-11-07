#ifndef __GAMEMENU_H__
#define __GAMEMENU_H__
#include "cocos2d.h"
USING_NS_CC;
class CGameMenu : public Scene
{
public:
	CGameMenu();
	~CGameMenu();
	virtual bool init();
	CREATE_FUNC(CGameMenu);
private:

};

#define WINSIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

#endif
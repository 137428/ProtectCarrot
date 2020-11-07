#ifndef __BUFF_H__
#define __BUFF_H__
#include "cocos2d.h"
#include "DataClass.h"
#include "BuffBase.h"
USING_NS_CC;
class CBuffSpeed : public CBuffBase
{
public:
	CBuffSpeed();
	~CBuffSpeed();
	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(CBuffSpeed);
private:
};

class CBuffHurt : public CBuffBase
{
public:
	CBuffHurt();
	~CBuffHurt();
	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(CBuffHurt);
private:
};

#endif
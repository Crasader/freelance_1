#ifndef __SMALL_ASTEROID_H__
#define __SMALL_ASTEROID_H__

#include "cocos2d.h"
USING_NS_CC;
class SmallAsteroid : public Sprite
{

public:
	SmallAsteroid();
	static SmallAsteroid* create(bool isLeft);
	bool setup(bool isLeft);

	void update();
	void destroy();

private:
	int delta;
	Sprite* ast;
	ParticleSun* fire;
};

#endif
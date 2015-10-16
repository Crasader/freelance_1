#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include "cocos2d.h"
#include "SmallAsteroid.h"
USING_NS_CC;
class SpaceShip : public Sprite
{

public:
	SpaceShip();
	static SpaceShip* create();
	bool init() override;


	void reset();
	SmallAsteroid* push();
	void update();

private:
	int delta;
};

#endif
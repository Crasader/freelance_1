#include "spaceship.h"
#define SPEED 6
SpaceShip* SpaceShip::create()
{
	auto space = new SpaceShip();
	space->initWithFile("asteroid.png");
	space->autorelease();
	return space;
}

bool SpaceShip::init()
{

	return true;
}

SmallAsteroid* SpaceShip::push()
{
	if (delta == 0) delta = SPEED;
	else {
		delta *= -1;
		this->stopAllActions();
		this->runAction(RepeatForever::create(RotateBy::create(1, (delta / SPEED) * 200)));
	}

	if (delta > 0){
		return SmallAsteroid::create(true);
	}
	else {
		return SmallAsteroid::create(false);
	}
}

SpaceShip::SpaceShip()
{
	delta = 0;
}

void SpaceShip::update()
{
	this->setPosition(this->getPosition() + Vec2(delta, -4));
}

void SpaceShip::reset()
{
	delta = 0;
	this->setRotation(0);
}


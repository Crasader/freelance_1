#include "SmallAsteroid.h"
#define SPEED 6
SmallAsteroid* SmallAsteroid::create(bool isLeft)
{
	auto space = new SmallAsteroid();
	space->init();
	space->setup(isLeft);
	
	space->autorelease();
	return space;
}

bool SmallAsteroid::setup(bool isLeft)
{
	ast = Sprite::create("asteroid.png");
	ast->setScale(0.2f);
	this->addChild(ast);
	fire = ParticleSun::create();
	fire->setPositionType(ParticleSystem::PositionType::FREE);
	fire->setSpeed(100);
	fire->setEmissionRate(100);
	fire->setLife(0.5f);
	//fire->setStartRadius(0);
	//fire->setStartRadiusVar(0);
	fire->setLife(0.2f);
	fire->setPosition(0, 0);
	this->addChild(fire);

	if (isLeft){
		delta = -6;
		ast->runAction(RepeatForever::create(RotateBy::create(1, (delta / SPEED) * 200)));
	}
	else {
		delta = 6;
		ast->runAction(RepeatForever::create(RotateBy::create(1, (delta / SPEED) * 200)));
	}

	return true;
}


SmallAsteroid::SmallAsteroid()
{
	delta = 0;
}

void SmallAsteroid::update()
{
	this->setPosition(this->getPosition() + Vec2(delta, -7));
}

void SmallAsteroid::destroy()
{
	fire->stopSystem();
	ast->setOpacity(0);
}


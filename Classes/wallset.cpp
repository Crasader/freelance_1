#include "wallset.h"
#define COCOS2D_DEBUG 1
#define SPACE 400

WallSet* WallSet::create()
{
	auto wall = new WallSet();
	wall->init(Vec2::ZERO);
	wall->autorelease();
	return wall;
}

void WallSet::init(Vec2 viewPoint)
{
	int i = 0;
	//endPoint = 1136 * 1.3f;
	endPoint = 0;
	while (i < 10){
		Wall* wall = Wall::create();
		wall->regen();
		wall->setPosition(0, endPoint);
		this->addChild(wall);
		walls.push_back(wall);
		endPoint -= SPACE;
		i++;
	}
}

cocos2d::Vec2 WallSet::getViewPoint()
{
	return _viewPoint;
}

void WallSet::setViewPoint(Vec2 viewPoint)
{
	_viewPoint = viewPoint;

	for(Wall* wall:walls)
	{
		if (wall->getPositionY() > -viewPoint.y + 1136 + 100){
			wall->regen();
			wall->setPosition(0, endPoint);
			endPoint -= SPACE;
		}
	}
}

bool WallSet::collis(Sprite* rect)
{
	for(Wall* wall:walls)
	{

		Rect shipRect = Rect(
			(float)(rect->getPosition().x - wall->getPositionX() - (rect->getContentSize().width / 2)),
			(float)(rect->getPosition().y - wall->getPositionY() - (rect->getContentSize().height / 2)),
			rect->getContentSize().width,
			rect->getContentSize().height);

		if (wall->collis(shipRect)) {
			
			return true;

		}
	}
	return false;
}

bool WallSet::checkScore(Sprite* rect)
{
	for (Wall* wall : walls)
	{
		if (wall->checkScore(rect))
			return true;
	}
	return false;
}


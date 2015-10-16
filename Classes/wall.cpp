#include "wall.h"
#define COCOS2D_DEBUG 1

Wall* Wall::create()
{
	auto wall = new Wall();
	wall->init();
	wall->regen();
	wall->autorelease();
	return wall;
}



bool Wall::collis(Rect rect)
{

		if (left->collis(rect) || right->collis(rect)) {
			return true;
		}

	return false;
}

Wall::Wall()
{
	left = NULL;
	right = NULL;
}

void Wall::regen()
{
	if (left == NULL){
		left = Block::create();
		left->setPosition(0, 0);
		this->addChild(left);
	}

	if (right == NULL){
		right = Block::create();
		right->setPosition(0, 0);
		this->addChild(right);
	}

	_scored = false;
	int space = 200;
	int randX = rand_0_1() * (640 - 40 - space);
	randX += 20;
	left->setPositionX(randX - left->getContentSize().width / 2);
	right->setPositionX(randX + space + right->getContentSize().width / 2);
}

bool Wall::checkScore(Sprite* rect)
{
	if (_scored) return false;
	if (left->checkScore(Vec2(rect->getPosition().x - this->getPositionX(), rect->getPosition().y - this->getPositionY()), rect->getContentSize().height)){
		_scored = true;
		return true;
	}
	return false;
}


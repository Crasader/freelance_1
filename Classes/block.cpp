#include "block.h"
#define COCOS2D_DEBUG 1

Block* Block::create()
{
	auto block = new Block();
	block->initWithFile("block.png");
	block->runAction(RepeatForever::create(Sequence::createWithTwoActions(FadeTo::create(1, 200), FadeTo::create(1, 255))));
// 	if (invisible){
// 		
// 		block->setOpacity(0);
// 	}
// 	block->setinvisible(invisible);

	block->autorelease();
	return block;
}


bool Block::collis(Rect rect)
{
	//
	//if (_invisible) return false;
	Rect blockRect = Rect(
		(float)(this->getPosition().x - (this->getContentSize().width / 2)),
		(float)(this->getPosition().y - (this->getContentSize().height / 2)),
		this->getContentSize().width,
		this->getContentSize().height);
	if (rect.intersectsRect(blockRect)){

		return true;
	}
	return false;
}

bool Block::checkScore(Vec2 pos, int height)
{
	float temp = this->getPositionY() - this->getContentSize().height / 2 - (pos.y + height / 2);
	if (temp < 20 && temp > 0)

		return true;
	else
		return false;
}


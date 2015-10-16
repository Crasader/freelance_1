#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
USING_NS_CC;
class Block : public Sprite
{

public:
	static Block* create();
	//bool init(bool invisible);
	
	bool collis(Rect rect);

	void resetScore();
	bool checkScore(Vec2 pos, int height);
private:
	
};

#endif
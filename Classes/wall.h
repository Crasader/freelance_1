#ifndef __WALL_H__
#define __WALL_H__

#include "cocos2d.h"
#include "block.h"
USING_NS_CC;
using namespace std;
class Wall: public Sprite
{

public:
	Wall();
	static Wall* create();

	bool collis(Rect rect);
	bool checkScore(Sprite* rect);
	void regen();
private:
	CC_SYNTHESIZE(bool, _scored, scored);
	Block* left;
	Block* right;
};

#endif
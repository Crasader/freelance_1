#ifndef __WALL_SET_H__
#define __WALL_SET_H__

#include "cocos2d.h"
#include "wall.h"
USING_NS_CC;
using namespace std;
class WallSet : public Sprite
{

public:
	static WallSet* create();
	void init(Vec2 viewPoint);
	void setViewPoint(Vec2 viewPoint);
	Vec2 getViewPoint();

	bool collis(Sprite* rect);
	bool checkScore(Sprite* rect);
private:
	int endPoint;
	Vec2 _viewPoint;
	vector<Wall*> walls;
};

#endif
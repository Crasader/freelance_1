#ifndef __MY_PARALAX_H__
#define __MY_PARALAX_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class MyParalax : public Sprite
{

public:
	MyParalax();
	static MyParalax* create(bool isFront);
	void move(int distance, Vec2 viewPoint);
	void setup(bool isFront);

private:
	int _distance;
	int _isFront;
	int endPoint1, endPoint2;

	vector<Sprite*> para1;
	vector<Sprite*> para2;

	Sprite* balloon;
	Sprite* plane;

	int delta;

};

#endif
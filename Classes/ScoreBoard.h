#ifndef __SCORE_BOARD_H__
#define __SCORE_BOARD_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class ScoreBoard : public Sprite
{

public:
	ScoreBoard();
	static ScoreBoard* create(int cur, int best);
	void setup(int cur, int best);

private:

};

#endif
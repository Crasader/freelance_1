#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{

}

ScoreBoard* ScoreBoard::create(int cur, int best)
{
	ScoreBoard* board = new ScoreBoard();
	//board->init();
	board->initWithFile("scoreBoard.png");
	board->setup(cur, best);
	board->autorelease();
	return board;
}

void ScoreBoard::setup(int cur, int best)
{
	auto label = Label::createWithTTF(CCString::createWithFormat("%d",cur)->getCString(), "fonts/Marker Felt.ttf", 40);
	label->enableOutline(Color4B::BLACK, 1);
	label->setAnchorPoint(Vec2(0, 0.5f));
	this->addChild(label);
	// position the label on the center of the screen
	label->setPosition(Vec2(150, 140));

	auto label2 = Label::createWithTTF(CCString::createWithFormat("%d", best)->getCString(), "fonts/Marker Felt.ttf", 40);
	label2->enableOutline(Color4B::BLACK, 1);
	label2->setAnchorPoint(Vec2(0, 0.5f));
	this->addChild(label2);
	// position the label on the center of the screen
	label2->setPosition(Vec2(125, 69));

}

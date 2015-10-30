#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "wallset.h"
#include "spaceship.h"
#include "SmallAsteroid.h"
#include "MyParalax.h"


USING_NS_CC;

class HelloWorld : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void pauseCallback(cocos2d::Ref* pSender);
	void playCallback(cocos2d::Ref* pSender);
	void leaderBoardCallback(cocos2d::Ref* pSender);
	void menuCallback(cocos2d::Ref* pSender);
	void replayCallback(cocos2d::Ref* pSender);
	void fbCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


	void update(float delta) override;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);

	virtual void onTouchMoved(Touch *touch, Event *unused_event);

	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	virtual void onTouchCancelled(Touch *touch, Event *unused_event);

private:

	void lose();
	void reset();
	int viewPoint;
	Sprite* mainSprite;
	Sprite* pausingSprite;
	WallSet* wallSet;
	SpaceShip* spaceShip;
	int speed;
	ParticleSystemQuad* fire;
	ParticleSystemQuad*	smoke;
	vector<SmallAsteroid*> sAst;
	vector<SmallAsteroid*> deleteList;
	vector<Node*> thingToDelete;
	MyParalax* paralax1;
	Label* scoreLabel;

	MenuItemImage* pauseItem;
	MenuItemImage* fbItem;
	MenuItemImage* playItem;
	MenuItemImage* leaderboardItem;
	MenuItemImage* menuItem;
	MenuItemImage* replayItem;

	int score;

	bool isPausing;
	bool endGame;
	bool isPlaying;
};

#endif // __HELLOWORLD_SCENE_H__

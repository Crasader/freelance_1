#include "HelloWorldScene.h"
#include "wall.h"
#include "ScoreBoard.h"
#include "base\CCUserDefault.h"
#include "SimpleAudioEngine.h"
#include "SonarFrameworks.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	isPausing = false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 winSize = Director::getInstance()->getWinSize();

	this->scheduleUpdate();

	
	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(0, 0);
	this->addChild(background);

	

	mainSprite = Sprite::create();
	mainSprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(mainSprite);

	

	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 40);
    
    // position the label on the center of the screen
	scoreLabel->setPosition(Vec2(winSize.x/2,
		winSize.y - scoreLabel->getContentSize().height));
	scoreLabel->enableOutline(Color4B::BLACK, 1);

    // add the label as a child to this layer
	this->addChild(scoreLabel);
	scoreLabel->setOpacity(0);

	pausingSprite = Sprite::create("blackdot.png");
	pausingSprite->setScale(MAX(winSize.x / pausingSprite->getContentSize().width, winSize.y / pausingSprite->getContentSize().height));
	pausingSprite->setAnchorPoint(Vec2(0, 0));
	
	this->addChild(pausingSprite);



    pauseItem = MenuItemImage::create(     "pause.png",
                                           "pause.png",
                                           CC_CALLBACK_1(HelloWorld::pauseCallback, this));
    
	pauseItem->setPosition(Vec2(pauseItem->getContentSize().width / 2 + 20,
		winSize.y - pauseItem->getContentSize().height / 2 - 20));
	pauseItem->setEnabled(false);
	pauseItem->setOpacity(0);

	menuItem = MenuItemImage::create("menu.png",
		"menuPress.png",
		CC_CALLBACK_1(HelloWorld::menuCallback, this));

	menuItem->setPosition(Vec2(winSize.x/2 + 95,
		winSize.y/2 - 100));
	menuItem->setEnabled(false);
	menuItem->setOpacity(0);

	replayItem = MenuItemImage::create("replay.png",
		"replayPress.png",
		CC_CALLBACK_1(HelloWorld::replayCallback, this));

	replayItem->setPosition(Vec2(winSize.x / 2 - 105,
		winSize.y/2 - 100));
	replayItem->setEnabled(false);
	replayItem->setOpacity(0);


	playItem = MenuItemImage::create(
		"play.png",
		"playPress.png",
		CC_CALLBACK_1(HelloWorld::playCallback, this));

	playItem->setPosition(Vec2(winSize.x / 2 - 150,
		winSize.y / 2));

	playItem->runAction(RepeatForever::create(Sequence::createWithTwoActions(ScaleTo::create(0.5f, 0.98f), ScaleTo::create(0.5f, 1))));

	leaderboardItem = MenuItemImage::create(
		"leaderboard.png",
		"leaderboardPress.png",
		CC_CALLBACK_1(HelloWorld::leaderBoardCallback, this));

	leaderboardItem->setPosition(Vec2(winSize.x / 2 + 150,
		winSize.y / 2));

	leaderboardItem->runAction(RepeatForever::create(Sequence::createWithTwoActions(ScaleTo::create(0.5f, 0.98f), ScaleTo::create(0.5f, 1))));
	

    // create menu, it's an autorelease object
	auto menu = Menu::create(pauseItem, playItem, replayItem, menuItem, leaderboardItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	isPlaying = false;
	
	reset();
	pauseItem->setEnabled(false);
	pauseItem->setOpacity(0);
	scoreLabel->setOpacity(0);
	pausingSprite->setOpacity(50);

	if (!SonarCocosHelper::GooglePlayServices::isSignedIn())
		SonarCocosHelper::GooglePlayServices::signIn();
    
    return true;
}

void HelloWorld::reset()
{
	Vec2 winSize = Director::getInstance()->getWinSize();
	mainSprite->removeAllChildren();
	for (auto node : thingToDelete){
		node->getParent()->removeChild(node);
	}
	thingToDelete.clear();
	sAst.clear();
	deleteList.clear();

	mainSprite->setPosition(0, 0);

	paralax1 = MyParalax::create(false);
	mainSprite->addChild(paralax1);

	wallSet = WallSet::create();
	wallSet->setPosition(0, 0);
	mainSprite->addChild(wallSet);

	viewPoint = 1136;

	smoke = ParticleSmoke::create();
	smoke->setPositionType(ParticleSmoke::PositionType::FREE);
	smoke->setSpeed(200);
	smoke->setEmissionRate(100);
	smoke->setTotalParticles(500);
	smoke->setLife(1);

	mainSprite->addChild(smoke);

	spaceShip = SpaceShip::create();
	spaceShip->setPosition(winSize.x / 2, 1136 - 300);
	mainSprite->addChild(spaceShip);
	smoke->setPosition(spaceShip->getPosition());

	fire = ParticleFire::create();
	fire->setPositionType(ParticleSystem::PositionType::FREE);
	fire->setSpeed(200);
	fire->setEmissionRate(200);
	fire->setTotalParticles(500);
	fire->setLife(2);
	fire->setPosition(spaceShip->getPosition());
	mainSprite->addChild(fire);

	viewPoint = 1136;
	endGame = false;
	isPausing = false;
	speed = 4;
	scoreLabel->setOpacity(0);
	pausingSprite->setOpacity(0);
	pauseItem->setEnabled(true);
	pauseItem->setOpacity(255);
	menuItem->setEnabled(false);
	menuItem->setOpacity(0);
	replayItem->setEnabled(false);
	replayItem->setOpacity(0);
	score = 0;
	scoreLabel->setString(CCString::createWithFormat("%d", score)->getCString());
	scoreLabel->setOpacity(255);

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update(float delta)
{
	if (isPlaying){
		if (!endGame){
			if (!isPausing){
				if (wallSet->collis(spaceShip) == false){
					spaceShip->update();

					Vec2 winSize = Director::getInstance()->getWinSize();
					if ((spaceShip->getPositionX() - spaceShip->getContentSize().width / 2 > winSize.x) || (spaceShip->getPositionX() + spaceShip->getContentSize().width / 2 < 0)){
						lose();
						return;
					}

					if (wallSet->checkScore(spaceShip)){
						score++;
						scoreLabel->setString(CCString::createWithFormat("%d", score)->getCString());
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/win.mp3", false, 1.0f);
					}

					vector<SmallAsteroid*> notDeleteList;
					for (auto ast : sAst){
						ast->update();
						if (wallSet->collis(ast)){

							deleteList.push_back(ast);
							ast->destroy();
							if (deleteList.size() > 10){
								mainSprite->removeChild(deleteList[0], true);
								deleteList.erase(deleteList.begin());
							}
						}
						else {
							notDeleteList.push_back(ast);
						}
					}
					sAst.swap(notDeleteList);


					fire->setPosition(spaceShip->getPosition() + Vec2(0, -20));
					smoke->setPosition(spaceShip->getPosition() + Vec2(0, -10));

					mainSprite->setPositionY(1136 - (spaceShip->getPositionY() + 300));
					wallSet->setViewPoint(mainSprite->getPosition());
					paralax1->move(4, mainSprite->getPosition());
				}
				else {
					lose();
					return;
				}
			}

		}
	}
	else {
		spaceShip->update();
		fire->setPosition(spaceShip->getPosition() + Vec2(0, -20));
		smoke->setPosition(spaceShip->getPosition() + Vec2(0, -10));

		mainSprite->setPositionY(1136 - (spaceShip->getPositionY() + 300));
		wallSet->setViewPoint(mainSprite->getPosition() + Vec2(0, 1300));
		paralax1->move(4, mainSprite->getPosition());
	}
		

}


bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (isPlaying){
		if (!isPausing){
			auto ast = spaceShip->push();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/poc.mp3", false, 1.0f);
			mainSprite->addChild(ast);
			sAst.push_back(ast);
			ast->setPosition(spaceShip->getPosition());

			speed++;
// 			if (endGame) {
// 
// 				auto scene = HelloWorld::createScene();
// 				Director::sharedDirector()->replaceScene(scene);
// 			}
		}
	}
	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void HelloWorld::onTouchCancelled(Touch *touch, Event *unused_event)
{

}

void HelloWorld::lose()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx/explosion.mp3", false, 1.0f);
	endGame = true;
	spaceShip->stopAllActions();
	spaceShip->setOpacity(0);
	fire->stopSystem();
	smoke->stopSystem();
	ParticleGalaxy* explose = ParticleGalaxy::create();
	explose->setPosition(spaceShip->getPosition());
	explose->setDuration(0.1f);
	explose->setLife(0.2f);
	explose->setEmissionRate(1000);
	explose->setStartSize(20);
	explose->setEndSize(20);
	explose->setSpeed(200);

	mainSprite->addChild(explose);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 winSize = Director::getInstance()->getWinSize();
	

	int best = UserDefault::getInstance()->getIntegerForKey("high_score", 0);
	if (score > best){
		UserDefault::getInstance()->setIntegerForKey("high_score", score);
	}
	pausingSprite->setOpacity(100);
	pauseItem->setEnabled(false);
	pauseItem->setOpacity(0);
	scoreLabel->setOpacity(0);
	ScoreBoard* board = ScoreBoard::create(score, best);
	this->addChild(board);
	board->setPosition(winSize.x / 2, winSize.y /2 + 100);
 	thingToDelete.push_back(board);


	replayItem->setEnabled(true);
	replayItem->setOpacity(255);
	menuItem->setEnabled(true);
	menuItem->setOpacity(255);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (!SonarCocosHelper::GooglePlayServices::isSignedIn()){
			SonarCocosHelper::GooglePlayServices::signIn();
			//SonarCocosHelper::GooglePlayServices::showLeaderboard("CgkI2dnm3N0XEAIQAA");

	}
	SonarCocosHelper::GooglePlayServices::submitScore("CgkI2dnm3N0XEAIQAA", score);
#endif

}

void HelloWorld::pauseCallback(cocos2d::Ref* pSender)
{
	if (!isPausing){
		isPausing = true;
		pauseItem->setEnabled(false);
		pauseItem->setOpacity(0);
		pausingSprite->setOpacity(100);
		playItem->setEnabled(true);
		playItem->setOpacity(255);
	}
}

void HelloWorld::playCallback(cocos2d::Ref* pSender)
{
	if (isPlaying){
		if (isPausing){
			isPausing = false;
			pauseItem->setEnabled(true);
			pauseItem->setOpacity(255);
			pausingSprite->setOpacity(0);
			playItem->setEnabled(false);
			playItem->setOpacity(0);
		}
	}
	else {
		scoreLabel->setOpacity(255);
		isPlaying = true;
		pauseItem->setEnabled(true);
		pauseItem->setOpacity(255);
		pausingSprite->setOpacity(0);
		playItem->setEnabled(false);
		playItem->setOpacity(0);
		playItem->stopAllActions();

		Vec2 winSize = Director::getInstance()->getWinSize();
		playItem->setPosition(Vec2(winSize.x / 2,
			winSize.y / 2));

		leaderboardItem->setEnabled(false);
		leaderboardItem->setOpacity(0);
		leaderboardItem->stopAllActions();
	}
}

void HelloWorld::menuCallback(cocos2d::Ref* pSender)
{
	auto scene = HelloWorld::createScene();
	Director::sharedDirector()->replaceScene(scene);
}

void HelloWorld::replayCallback(cocos2d::Ref* pSender)
{
	reset();
}

void HelloWorld::leaderBoardCallback(cocos2d::Ref* pSender)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (!SonarCocosHelper::GooglePlayServices::isSignedIn()){
			SonarCocosHelper::GooglePlayServices::signIn();

	}
	SonarCocosHelper::GooglePlayServices::showLeaderboard("CgkI2dnm3N0XEAIQAA");
#endif
}



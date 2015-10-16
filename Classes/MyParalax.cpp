#include "MyParalax.h"
#define WITDH 640
#define HEIGHT 1136

MyParalax::MyParalax()
{
	_isFront = false;
	_distance = 0;
	endPoint1 = -0;
	endPoint2 = -0;
}

MyParalax* MyParalax::create(bool isFront)
{
	MyParalax* palax = new MyParalax();
	palax->init();
	palax->setup(isFront);
	palax->autorelease();
	return palax;
}

void MyParalax::move(int distance, Vec2 viewPoint)
{
	balloon->setPositionY(balloon->getPositionY() - distance / 2);
	if (balloon->getPositionY() > -viewPoint.y + 1136 + balloon->getContentSize().height){
		balloon->setPosition(rand_0_1()*(WITDH - 100) + 50, -viewPoint.y - (rand_0_1()*HEIGHT + HEIGHT));
	}

	plane->setPosition(plane->getPositionX() + delta,plane->getPositionY() - distance / 2);
	if (plane->getPositionY() > -viewPoint.y + 1136 + plane->getContentSize().height){
		float ran = rand_0_1();
		if (ran > 0.5f){
			delta = 1;
			plane->setPosition(rand_0_1()*(WITDH )/2, -viewPoint.y - (rand_0_1()*HEIGHT + 0));
			plane->setFlipX(false);
		}
		else {
			delta = -1;
			plane->setPosition(rand_0_1()*(WITDH) / 2 + (WITDH) / 2, -viewPoint.y - (rand_0_1()*HEIGHT + 0));
			plane->setFlipX(true);
		}
		
	}

	for (auto cloud : para1){
		cloud->setPositionY(cloud->getPositionY() - distance / 2);
		//if (cloud->getPositionY() < endPoint1)
		//	endPoint1 = cloud->getPositionY();
		if (cloud->getPositionY() > -viewPoint.y + 1136 + cloud->getContentSize().height){
			//endPoint1 -= rand_0_1()*HEIGHT + HEIGHT;
			cloud->setPosition(rand_0_1()*WITDH, -viewPoint.y - rand_0_1()*HEIGHT - cloud->getContentSize().height / 2);
			cloud->setScale(0.5f + rand_0_1()*0.5f);
		}
	}


	for (auto cloud : para2){
		cloud->setPositionY(cloud->getPositionY() - distance / 3);
		//if (cloud->getPositionY() < endPoint2)
		//	endPoint1 = cloud->getPositionY();
		if (cloud->getPositionY() > -viewPoint.y + 1136 + cloud->getContentSize().height){
			//endPoint2 -= rand_0_1()*HEIGHT + HEIGHT;
			cloud->setPosition(rand_0_1()*WITDH, -viewPoint.y - rand_0_1()*HEIGHT - cloud->getContentSize().height / 2);
			cloud->setScale(0.5f + rand_0_1()*0.5f);
		}
	}
}

void MyParalax::setup(bool isFront)
{
	balloon = Sprite::create("balloon.png");
	this->addChild(balloon);
	balloon->setPosition(rand_0_1()*(WITDH - 100) + 50, -(rand_0_1()*HEIGHT + HEIGHT));

	plane = Sprite::create("plane.png");
	this->addChild(plane);
	plane->setPosition(rand_0_1()*(WITDH) / 2, -(rand_0_1()*HEIGHT + 0));
	delta = 1;

	Sprite* cloud = Sprite::create("cloud1.png");
	this->addChild(cloud);
	endPoint1 -= rand_0_1()*HEIGHT;
	cloud->setPosition(rand_0_1()*WITDH, endPoint1);
	cloud->setScale(0.5f + rand_0_1()*0.5f);
	para1.push_back(cloud);

	cloud = Sprite::create("cloud2.png");
	this->addChild(cloud);
	endPoint1 -= rand_0_1()*HEIGHT;
	cloud->setPosition(rand_0_1()*WITDH, endPoint1);
	cloud->setScale(0.5f + rand_0_1()*0.5f);
	para1.push_back(cloud);

	cloud = Sprite::create("cloud1.png");
	this->addChild(cloud);
	endPoint2 -= rand_0_1()*HEIGHT;
	cloud->setPosition(rand_0_1()*WITDH, endPoint2);
	cloud->setScale(0.5f + rand_0_1()*0.5f);
	para2.push_back(cloud);

	cloud = Sprite::create("cloud2.png");
	this->addChild(cloud);
	endPoint2 -= rand_0_1()*HEIGHT;
	cloud->setPosition(rand_0_1()*WITDH, endPoint2);
	cloud->setScale(0.5f + rand_0_1()*0.5f);
	para2.push_back(cloud);

	
}


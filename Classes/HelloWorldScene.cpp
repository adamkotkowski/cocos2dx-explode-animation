#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Explosion.hpp"

USING_NS_CC;

using namespace cocostudio::timeline;

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
	
	auto rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);
	
	this->scheduleOnce(schedule_selector(HelloWorld::explode1), 1.f);
	this->scheduleOnce(schedule_selector(HelloWorld::explode2), 2.f);
	this->scheduleOnce(schedule_selector(HelloWorld::explode3), 3.f);
	
	
	return true;
}
void HelloWorld::explode1(float dt){
	Vec3 crashVector(0,10,0);
	float duration = 10;
	float explosionPower = 1000;
	float gravity = 10000;
	
	auto explodeAnimation = util::Explosion::create(duration, crashVector, explosionPower, gravity);
	this->getChildByName("Scene3D")->getChildByName("monkey-1")->runAction(explodeAnimation);
}
void HelloWorld::explode2(float dt){
	auto explodeAnimation = util::Explosion::create(100, Vec3(10,0,0), 1000, 10000);
	this->getChildByName("Scene3D")->getChildByName("monkey-2")->runAction(explodeAnimation);
}
void HelloWorld::explode3(float dt){
	auto explodeAnimation = util::Explosion::create(100, Vec3(0,10,0), 1000, 10000);
	this->getChildByName("Scene3D")->getChildByName("monkey-3")->runAction(explodeAnimation);
}

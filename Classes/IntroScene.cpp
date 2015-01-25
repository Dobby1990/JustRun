#include "IntroScene.h"
#include "Definitions.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* IntroScene::createScene(){
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = IntroScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	CCLOG("IntroScene added to layer");

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroScene::init(){
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ){
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CCLOG("passed visibleSize and origin");

	////SCROLLING BG/////
		for (int i = 0; i < 2; i++){
			backgroundSpriteArray[i] = Sprite::create("background.png");
			backgroundSpriteArray[i]->setPosition
			(Point((visibleSize.width) + origin.x, (-1 * visibleSize.height * i) + (visibleSize.height / 2) + origin.y));
			backgroundSpriteArray[i]->setScale(visibleSize.width * 2 / backgroundSpriteArray[i]->getContentSize().width, visibleSize.height / backgroundSpriteArray[i]->getContentSize().height);
			this->addChild(backgroundSpriteArray[i], -2);
		}
	/////////////////AUDIO CODE////////////
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/Moo.wav");

	auto cow =  Sprite::create("animations/Cow_0.png");
	auto ship = Sprite::create("ufo.png");
	auto beam = Sprite::create("tractor_beam.png");

	CCLOG("passed sprite creation");

	cow->setScale(0.2, 0.2);
	ship->setScale(0.5, 0.5);
	beam->setScale(0.5, 1.0);

	ship->setPosition(Point(origin.x - ship->getContentSize().width, visibleSize.height - ship->getContentSize().height));
	beam->setPosition(Point(ship->getPositionX(), ship->getPositionY() - beam->getContentSize().height));
	cow->setPosition(Point(ship->getPositionX(), visibleSize.height / 2 + origin.y));

	this->addChild(cow);
	this->addChild(beam);
	this->addChild(ship);

	auto moveShip = MoveTo::create(1.0f, Point(visibleSize.width / 2 + origin.x, (visibleSize.height + ship->getPositionY()) / 2 + origin.y));
	auto moveBeam = MoveTo::create(1.0f, Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ));
	auto moveCow = MoveTo::create(1.0f, Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	ship->runAction(moveShip);
	beam->runAction(moveBeam);
	cow->runAction(moveCow);

    this->scheduleOnce(schedule_selector(IntroScene::goToGameScene), 2.0f);
    return true;
}

void IntroScene::goToGameScene(float dt){
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
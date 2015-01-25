#include "GameOver.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

int GameOver::scorex = 0;
Scene* GameOver::createScene(int i){
	auto scene = Scene::create();
	//scene->getPhysicsWorld()->setAutoStep(false);

	scorex = i;
	// 'layer' is an autorelease object
	auto layer = GameOver::create();
	
	// add layer as a child to scene
	scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init(){
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    /////////////////AUDIO CODE////////////
   	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/Moo.wav");
 
    auto background = Sprite::create("GameOverBack.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height/2 + origin.y));
    background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);

    
    
    this->addChild(background);

    labelScore(0.23);

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Moo.wav");


	return true;
}

void GameOver::labelScore(float dt) {
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	char buffer[20];
	sprintf(buffer, "%i", GameOver::getScoreX());
	auto score1 = Label::createWithTTF(buffer, "fonts/Marker Felt.ttf", 32);
	score1->setPosition(Point(origin.x, origin.y + visibleSize.height - 80));
	score1->setAlignment(TextHAlignment::LEFT);
	score1->setAnchorPoint(Point(0.0f, 0.0f));

	this->addChild(score1);
}

int GameOver::getScoreX(){
	return scorex;
}

#include "GameScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "GameOver.h"

USING_NS_CC;

Scene* GameScene::createScene(){
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, -300));
	//scene->getPhysicsWorld()->setAutoStep(false);

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init(){
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Soundtrack preload
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/soundtrack.wav");

    /**
	auto background = Sprite::create("Background.png");
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(background);
	*/

	////SCROLLING BG/////
	for (int i = 0; i < 2; i++){
		backgroundSpriteArray[i] = Sprite::create("background.png");
		backgroundSpriteArray[i]->setPosition
		(Point((visibleSize.width) + origin.x, (-1 * visibleSize.height * i) + (visibleSize.height / 2) + origin.y));
		backgroundSpriteArray[i]->setScale(visibleSize.width * 2 / backgroundSpriteArray[i]->getContentSize().width, visibleSize.height / backgroundSpriteArray[i]->getContentSize().height);
		this->addChild(backgroundSpriteArray[i], -2);
	}

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 10);
	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();

	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x,visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
    
    
    edgeBody->setDynamic(false);

    
	this->addChild(edgeNode);


	player = new Player(this);
	ufo = new Ufo(this);
	ufo->wiggleUfo(1.0);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	

    
	this->schedule(schedule_selector(GameScene::spawnPlatform), PLATFORM_SPAWN_TIME*visibleSize.width);
    this->schedule(schedule_selector(GameScene::calScore), PLATFORM_SPAWN_TIME*visibleSize.width);
    
    this->spawnStartPlatform();
    
    // this->addChild(score1);
    // Score label
    score = 0;
    testScore = 0;
    auto *tempScore = __String::createWithFormat("SCORE: %i", testScore);
    scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", 50);
    scoreLabel->setPosition(Point(origin.x + 120, origin.y + visibleSize.height - 80));
    this->addChild(scoreLabel);
    
	this->scheduleUpdate();


	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/soundtrack.wav", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);

    return true;
}

bool GameScene::onContactBegin(PhysicsContact &contact){

	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();


	if ((PLAYER_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask())
		||
		(PLAYER_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask())){

		CCLOG("Collided");
        
//		auto scene = GameOver::createScene();
//		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}

	return true;
}



bool GameScene::onTouchBegan(Touch *touch, Event * event){

	player->Jump();

	this->scheduleOnce(schedule_selector(GameScene::StopJumping), PLAYER_JUMP_DURATION);

	return true;
}

void GameScene::StopJumping(float dt){
	player->StopJump();
}


void GameScene::update(float dt){
	player->Fall();

	///update scrolling BG
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < 2; i++){
		if (backgroundSpriteArray[i]->getPosition().x <= 0){
			backgroundSpriteArray[i]->setPosition(
					Point((visibleSize.width) + getPosition().x, (visibleSize.height / 2)));
		}
	}
	for (int i = 0; i < 2; i++){
		backgroundSpriteArray[i]->setPosition(
			Point(	backgroundSpriteArray[i]->getPosition().x - 4.0,
					backgroundSpriteArray[i]->getPosition().y));
	}

    if(player->getY() <= player->getSpriteLength().height/6.0) {
        CCLOG("Collided 1");
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        auto scene = GameOver::createScene(score);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
    //update score and score label
    calScore(1.0);
    auto *tempScore = __String::createWithFormat("SCORE: %i", score);
    scoreLabel->setString(tempScore->getCString());
    scoreLabel->setPosition(Point(origin.x + 120, origin.y + visibleSize.height - 80));
}

void GameScene::spawnPlatform(float dt) {
	platform.spawnPlatform(this);
}

void GameScene::spawnStartPlatform(){
    platform.startPlatform(this);
}

void GameScene::calScore(float dt) {
    score++;
    CCLOG("Score: %i", score);
}

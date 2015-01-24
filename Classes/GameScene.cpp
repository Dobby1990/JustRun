#include "GameScene.h"
#include "Definations.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto background = Sprite::create("Background.png");
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
	background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(background);

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 10);
	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();

	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x,visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);


	player = new Player(this);
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	
	this->schedule(schedule_selector(GameScene::spawnPlatform), PLATFORM_SPAWN_TIME*visibleSize.width);

	this->scheduleUpdate();
    return true;
}

bool GameScene::onContactBegin(PhysicsContact &contact){

	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if ((PLAYER_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask()
		||
		(PLAYER_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))){

		CCLOG("Collided");

		//auto scene = GameOverScene::createScene();
		//Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
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
}


void GameScene::spawnPlatform(float dt) {
	platform.spawnPlatform(this);
}

#include "Player.h"
#include "Definations.h"

USING_NS_CC;

Player::Player(Layer *layer){

	visbleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	player = Sprite::create("Cow_1w.png");
	player->setScale(0.2, 0.2);
	player->setPosition(Point(visbleSize.width / 2 + origin.x, visbleSize.height / 2 + origin.y));


	//auto playerBody = PhysicsBody::createBox((player->getContentSize().width /2) * 0.2);
	auto playerBody = PhysicsBody::createBox(player->getContentSize() * 0.2);
	player->setPhysicsBody(playerBody);

	playerBody->setDynamic(true);
	playerBody->setGravityEnable(true);
	playerBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
	playerBody->setContactTestBitmask(true);
	layer->addChild(player, 100);

	isJumping = false;
}


void Player::Fall(){

	if (isJumping == true){
		player->setPositionX(visbleSize.width / 2 + origin.x);
		player->setPositionY(player->getPositionY() + (visbleSize.height /2 * PLAYER_JUMP_SPEED));
	}
	else{
		player->setPositionX(visbleSize.width / 2 + origin.x);
		player->setPositionY(player->getPositionY() - (PLAYER_FALL_SPEED ));
	}
}











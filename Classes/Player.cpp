#include "Player.h"
#include "Definitions.h"

USING_NS_CC;

Player::Player(Layer *layer){

	visbleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();


	//////////////////////ANIMATION CODE/////////
	player = Sprite::create("sprites/cow/Cow_0.png");
	Vector<SpriteFrame*> animFrames(3);
	char str[100] = {0};
	for(int i = 1; i < 3; i++){
	    sprintf(str, "sprites/cow/Cow_%d.png",i);
	    auto frame = SpriteFrame::create(str,Rect(0,0,540,540)); //we assume that the sprites' dimentions are 540*540 rectangles.
	    animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.4f);
    
	player->runAction( RepeatForever::create( Animate::create(animation) ));
	//////////////////ANIMATION CODE/////////

	player->setScale(0.3, 0.3);
	player->setPosition(Point(visbleSize.width / 2 + origin.x, visbleSize.height / 2 + origin.y));


	//auto playerBody = PhysicsBody::createBox((player->getContentSize().width /2) * 0.2);
	auto playerBody = PhysicsBody::createBox(player->getContentSize() * 0.3);
	player->setPhysicsBody(playerBody);
    

	playerBody->setDynamic(true);
	playerBody->setGravityEnable(true);
	playerBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
	playerBody->setContactTestBitmask(true);
    playerBody->setAngularVelocityLimit(0.2);
	layer->addChild(player, 100);

	isJumping = false;
}


void Player::Fall(){

	if (isJumping == true){
		player->setPositionX(visbleSize.width / 2 + origin.x);
		player->setPositionY(player->getPositionY() + (visbleSize.height /2 * PLAYER_JUMP_SPEED));

		//////Jump Animation
		Vector<SpriteFrame*> animFrames(1);
		char str[100] = {0};
		sprintf(str, "sprites/cow/Cow_3.png");
		auto frame = SpriteFrame::create(str,Rect(0,0,540,540)); //we assume that the sprites' dimentions are 540*540 rectangles.
		animFrames.pushBack(frame);
		auto animation = Animation::createWithSpriteFrames(animFrames, 0.4f);
		auto animate = Animate::create(animation);
		player->runAction(animate);

	}
	else{
		player->setPositionX(visbleSize.width / 2 + origin.x);
		player->setPositionY(player->getPositionY() - (PLAYER_FALL_SPEED ));
	}
}

float Player::getX() {
    return player->getPositionX();
}

float Player::getY() {
    return player->getPositionY();
}

Size Player::getSpriteLength(){
    return visbleSize;
}











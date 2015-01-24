#include "Platform.h"
#include "Definations.h"

USING_NS_CC;


Platform::Platform() {
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin      = Director::getInstance()->getVisibleOrigin();

}

void Platform::spawnPlatform(cocos2d::Layer *layer) {
    
    CCLOG("New platform has spawned.....");
    
    //Create images for platforms
    auto topPlatform = Sprite::create("platform.png");
	auto bottomPlatform = Sprite::create("platform.png");
    
    
    //Create sprite physics body around platform one/two
    auto topPlatformBody = PhysicsBody::createBox(topPlatform->getContentSize());
    auto bottomPlatformBody = PhysicsBody::createBox(bottomPlatform->getContentSize());


    //Random variable for creating variation in height of platforms
    auto random = CCRANDOM_0_1();
    
    bool checked = true;
    
    auto previous = 0.0;
    
    if(checked) {
     previous = random;
    }
    
    if(random <= 0.20) {
        random = 0.20;
        checked = false;
    }
    if(random <= 0.40) {
        random = 0.40;
        checked = false;
    }
    else if(random <= 60) {
        random = 0.60;
        checked = false;
    }
    else if(random <= 80) {
        random = 0.80;
        checked = false;
    }
    else {
        random = 0.90;
    }
    
    if(random >= previous + 0.30) {
        random = previous+20;
    }
    if(random - previous <=0.10) {
        random+=0.10;
    }
    else if(previous - random >=0.40) {
        random+=0.10;
    }

    
    
    auto platform1TopPos = (random*visibleSize.height) + (topPlatform->getContentSize().height/2);
    
    auto platform1BotPos = (random*visibleSize.width) + (topPlatform->getContentSize().width/2);
    
	topPlatformBody->setDynamic(false);
	bottomPlatformBody->setDynamic(false);

    
    //Assign collision physics body to platforms
    topPlatform->setPhysicsBody(topPlatformBody);
    bottomPlatform->setPhysicsBody(bottomPlatformBody);

    
    topPlatform->setPosition(Point(visibleSize.width+topPlatform->getContentSize().width+origin.x, platform1TopPos));
    bottomPlatform->setPosition(Point(visibleSize.width+bottomPlatform->getContentSize().width+origin.x, platform1TopPos));
    
    auto topPlatformAction = MoveBy::create(PLATFORM_MOVE_SPEED*visibleSize.width, Point(-visibleSize.width*1.85,0));
    
    topPlatform->runAction(topPlatformAction);
    
    //bottomPlatform->setPosition(Point());
    
    layer->addChild(topPlatform);
    
}





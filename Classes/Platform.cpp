#include "Platform.h"


USING_NS_CC;


Platform::Platform() {
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin        = Director::getInstance()->getVisibleOrigin();
}

void Platform::spawnPlatform(cocos2d::Layer *layer) {
    
    CCLOG("New platform has spawned.....");
    
    //Create images for platforms
    auto topPlatform = Sprite::create("platform.png");
    auto bottomPlatform = Sprite::create("platform.png");
    
    
    //Create sprite physics body around platform one/two
    auto topPlatformBody = PhysicsBody::createBox(topPlatform->getContentSize());
    auto bottomPlatformBody = PhysicsBody::createBox(bottomPlatform->getContentSize());
    

    auto edgeNode = Node::create();
    
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x,visibleSize.height / 2 + origin.y));

    
    this->addChild(edgeNode);
    
    topPlatformBody->setDynamic(false);

    
    //Random variable for creating variation in height of platforms
    auto random = CCRANDOM_0_1();
    
    bool checked = true;
    
    auto previous = 0.0;
    
    if(checked) {
      previous = random;
    }

    
    if(random <= 0.33) {
        random = 0.20;
        checked = false;
    }
    else if(random <= 0.66) {
        random = 0.40;
        checked = false;
    }
    else {
        random = 0.60;
        checked = false;
    }

    
    
    auto platform1TopPos = (random*visibleSize.height) + (topPlatform->getContentSize().height/2);
    
    auto platform1BotPos = (random*visibleSize.width) + (topPlatform->getContentSize().width/2);
    
    auto transBody = (visibleSize.width)+(topPlatform->getContentSize().width/2);

    
    topPlatformBody->setDynamic(false);
    bottomPlatformBody->setDynamic(false);

    
    //Assign collision physics body to platforms
    topPlatform->setPhysicsBody(topPlatformBody);
    bottomPlatform->setPhysicsBody(bottomPlatformBody);

    
    topPlatform->setPosition(Point(visibleSize.width+topPlatform->getContentSize().width+origin.x, platform1TopPos));
    bottomPlatform->setPosition(Point(visibleSize.width+bottomPlatform->getContentSize().width+origin.x, platform1TopPos));
    
    
    auto topPlatformAction = MoveBy::create((speed*visibleSize.width), Point(-visibleSize.width*1.85,0));
   
    if(speed >= 0.002400) {
        speed-=0.0004;
    }
    
    CCLOG("Speed: %f", speed);
    
    topPlatform->runAction(topPlatformAction);
    layer->addChild(topPlatform);
}


void Platform::startPlatform(Layer *layer){
    
    auto startPlatform = Sprite::create("platform.png");
    auto startPlatformBody = PhysicsBody::createBox(startPlatform->getContentSize());
    
    startPlatformBody->setDynamic(false);
    
    startPlatform->setPhysicsBody(startPlatformBody);
    
    startPlatform->setPosition(Point(visibleSize.width - (startPlatform->getContentSize().width / 6) , visibleSize.height / 2 - startPlatform->getContentSize().height));
    startPlatform->setScaleX(2);
    auto startPlatformAction = MoveBy::create((speed*visibleSize.width), Point(-visibleSize.width*1.850, 0));
    startPlatform->runAction(startPlatformAction);
    layer->addChild(startPlatform);
    
}





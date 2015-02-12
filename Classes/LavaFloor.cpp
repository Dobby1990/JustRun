#include "LavaFloor.h"
#include "Definitions.h"


USING_NS_CC;


LavaFloor::LavaFloor(Layer *layer) {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    lavaFloor = Sprite::create("sprites/lavaFloor.png");


    lavaFloorOrigin = new Point(Point(visibleSize.width / 2 + origin.x , lavaFloor->getContentSize().height / 2));

    lavaFloor->setPosition(Point(lavaFloorOrigin->x, lavaFloorOrigin->y));

    layer->addChild(lavaFloor, 100);
}





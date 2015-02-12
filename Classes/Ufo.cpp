#include "Ufo.h"
#include "Definitions.h"


USING_NS_CC;


Ufo::Ufo(Layer *layer) {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    ship = Sprite::create("sprites/ufo.png");
    beam = Sprite::create("sprites/tractor_beam.png");

    ship->setScale(0.5, 0.5);
    beam->setScale(0.5, 1.0);

    shipOrigin = new Point(Point(ship->getContentSize().width / 2 + origin.x , visibleSize.height - ship->getContentSize().height / 2));
    beamOrigin = new Point(Point(shipOrigin->x , shipOrigin->y - beam->getContentSize().height / 2));

    ship->setPosition(Point(shipOrigin->x, shipOrigin->y));
    beam->setPosition(Point(beamOrigin->x, beamOrigin->y));

    layer->addChild(beam);
    layer->addChild(ship);
}

void Ufo::wiggleUfo(float dt) {

    CCLOG("Wiggle Ufo.....");
    auto delay = DelayTime::create(0.25f);

    auto moveShipRight = MoveTo::create(1.0f, Point(shipOrigin->x + UFO_WHIGGLE_DELTA , shipOrigin->y));
    auto moveShipLeft = MoveTo::create(1.0f, Point(shipOrigin->x - UFO_WHIGGLE_DELTA , shipOrigin->y));

    auto moveBeamRight = MoveTo::create(1.0f, Point(beamOrigin->x + UFO_WHIGGLE_DELTA , beamOrigin->y));
    auto moveBeamLeft = MoveTo::create(1.0f, Point(beamOrigin->x - UFO_WHIGGLE_DELTA , beamOrigin->y));

    auto seqShip = Sequence::create(moveShipRight, moveShipLeft, moveShipRight->clone(), nullptr);
    auto seqBeam = Sequence::create(moveBeamRight, moveBeamLeft, moveBeamRight->clone(), nullptr);

    ship->runAction(RepeatForever::create(seqShip));
    beam->runAction(RepeatForever::create(seqBeam));
}


void Ufo::moveTo(Point *target){
	//if more time implement for easing intro scene
}





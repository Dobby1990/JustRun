#include "MeatBone.h"
#include "Definitions.h"


USING_NS_CC;


MeatBone::MeatBone(Layer *layer, Player *player) {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    meatBone = Sprite::create("sprites/meatOnBone.png");

    meatBone->setScale(0.5, 0.5);

    meatBoneOrigin = new Point(player->getX() , player->getY());

    meatBone->setPosition(Point(meatBoneOrigin->x, meatBoneOrigin->y));

    layer->addChild(meatBone);
}

void MeatBone::spawn(float dt) {

    CCLOG("Spawn MeatBone.....");
    auto delay = DelayTime::create(0.25f);

    auto rotate = RotateBy::create(1.0f, 360.0f);
    //meatBone->getContentSize().height * 4 as Y value
    auto move = MoveBy::create(1.0f, Vec2(0, visibleSize.height/2 ));
    auto move_back = MoveBy::create(1.0f, Vec2(0, -1 * (visibleSize.height + meatBone->getContentSize().height) /2));

    auto move_ease_out = EaseOut::create(move->clone(), 1.0f);
    auto move_ease_in = EaseIn::create(move_back->clone(), 1.0f);

    auto spawnIn = Spawn::createWithTwoActions(move_ease_out, rotate);
    auto spawnOut = Spawn::createWithTwoActions(move_ease_in, rotate->clone());

    auto sequence = Sequence::create(spawnIn, spawnOut, nullptr);

    meatBone->runAction(sequence);

}

float MeatBone::getY(){
	return	meatBone->getPositionY();
}

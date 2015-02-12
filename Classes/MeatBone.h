#ifndef __MEATBONE_H__
#define __MEATBONE_H__

#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;

class MeatBone {
public:
	MeatBone(Layer *layer, Player *player);

    void spawn(float dt);
    float getY();

 private:

     Size visibleSize;
     Vec2 origin;
     Sprite *meatBone;
     Point *meatBoneOrigin;
};

#endif // __MEATBONE_H__

#ifndef __LAVAFLOOR_H__
#define __LAVAFLOOR_H__

#include "cocos2d.h"
USING_NS_CC;

class LavaFloor {
public:
	LavaFloor(Layer *layer);

 private:

     Size visibleSize;
     Vec2 origin;
     Sprite *lavaFloor;
     Point *lavaFloorOrigin;
};

#endif // __LAVAFLOOR_H__

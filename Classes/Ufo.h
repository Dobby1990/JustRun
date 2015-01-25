#ifndef __UFO_H__
#define __UFO_H__

#include "cocos2d.h"
USING_NS_CC;

class Ufo {
public:
	Ufo(Layer *layer);

    void wiggleUfo(float dt);
    void moveTo(Point *target);

 private:

     Size visibleSize;
     Vec2 origin;
     Sprite *ship;
     Sprite *beam;
     Point *shipOrigin;
     Point *beamOrigin;
};

#endif // __UFO_H__

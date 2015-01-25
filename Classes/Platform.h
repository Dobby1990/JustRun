#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "cocos2d.h"
#include "Definitions.h"

class Platform : public cocos2d::Layer {
    
    public:
    
        Platform();
        void startPlatform(Layer *layer);
        void spawnPlatform(cocos2d::Layer *layer);
    
    
        CREATE_FUNC(Platform);
    
    private:
    
        cocos2d::Size visibleSize;
        cocos2d::Vec2 origin;
        float speed = PLATFORM_MOVE_SPEED;
};

#endif // __PLATFORM_H__

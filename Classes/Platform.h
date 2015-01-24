#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "cocos2d.h"
USING_NS_CC;

class Platform : public cocos2d::Layer {
    
    public:
    
        Platform();
        void spawnPlatform(cocos2d::Layer *layer);
    
        CREATE_FUNC(Platform);
    
    private:
    
        Size visibleSize;
        Vec2 origin;
};

#endif // __PLATFORM_H__

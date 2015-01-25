#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"


class GameOver : public cocos2d::Layer {
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int i);
    void labelScore(float dt);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    int getScoreX();
    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);

private:
    static int scorex;
};

#endif // __GAME_SCENE_H__

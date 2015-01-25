#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Platform.h"

class GameScene : public cocos2d::Layer{
public:

	int score;

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
        
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    
	void SetPhysicsWorld(PhysicsWorld *world) { sceneWorld = world; };
	bool onContactBegin(PhysicsContact &contact);
	bool onTouchBegan(Touch *touch, Event * event);
	void StopJumping(float dt);
	void update(float dt);
	cocos2d::Sprite *backgroundSpriteArray[2];
	void spawnPlatform(float dt);
    void spawnStartPlatform();
    void calScore(float dt);

	PhysicsWorld *sceneWorld;
	Player *player;
	Platform platform;
};

#endif // __GAME_SCENE_H__

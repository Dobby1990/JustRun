#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
USING_NS_CC;
class Player
{
public:
	Player(Layer *layer);

	void Fall();
	void Jump() { isJumping = true; };
	void StopJump() { isJumping = false; };

private:
	Size visbleSize;
	Vec2 origin;
	Sprite *player;

	bool isJumping;

};

#endif // __PLAYER_H__







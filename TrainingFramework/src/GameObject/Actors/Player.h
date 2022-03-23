#pragma once
#include <iostream>
#include "GameManager/ResourceManagers.h"
#include "Actor.h"

class SpriteAnimation;

enum class MoveState {
	IDLE = 0,
	MOVE_RIGHT = 1,
	MOVE_LEFT = -1
};

enum class JumpState {
	IDLE = 0,
	JUMPING = 1,
};

class Player : public Actor {
private:
	MoveState moveState;
	JumpState jumpState;
	int velocityScale;
public:
	void init() override;
	void update(float deltaTime) override;
	void draw() override;

	void moveRight();
	void horizontalMove(MoveState moveState, int velocityScale);

	void stopMove();
};
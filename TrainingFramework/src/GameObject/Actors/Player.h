#pragma once
#include <iostream>
#include "Actor.h"
#include "SpriteAnimation.h"

class Texture;

enum class MoveState {
	IDLE = 0,
	MOVE_RIGHT = 1,
	MOVE_LEFT = -1
};

enum class JumpState {
	LANDING = 0,
	JUMPING = 1,
	FALLING = 2,
};

class Player : public Actor {
private:
	MoveState	moveState;
	JumpState	jumpState;
	float		velocityScale;
	float		totalTime;
	float		jumpSpeed;
	bool		playing;
	bool		died;

	std::shared_ptr<SpriteAnimation> IDLE_Animation;
	std::shared_ptr<SpriteAnimation> move_Animation;
	std::shared_ptr<SpriteAnimation> jump_Animation;
public:
	Player();
	~Player();

	void init(float x_location, float y_location) override;
	void update(float deltaTime) override;
	void draw() override;

	virtual void initCollisionBox(float x_location, float y_location, float width, float height);
	void consumeCollision() override;

	void horizontalMove(MoveState moveState);
	void jump();
	void land();
	void stopMove();
	void die();
};
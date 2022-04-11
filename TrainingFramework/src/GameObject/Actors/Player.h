#pragma once
#include <iostream>
#include "Actor.h"
#include "SpriteAnimation.h"

class Texture;

enum class MoveState {
	IDLE = 0,
	MOVE_RIGHT = 1,
	MOVE_LEFT = -1,
	MOVE_DOWN = 2,
	MOVE_UP = -2,
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
	float		dieTime;
	float		jumpSpeed;
	bool		playing;
	bool		died;
	bool		dying;

	bool		movingUp;
	bool		movingLeft;
	bool		movingDown;
	bool		movingRight;

	int keyMoveLeft;
	int keyMoveRight;
	int keyJump;
	int keyMoveUp;
	int keyMoveDown;

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

	void bindKeys(int keyMoveLeft, int keyMoveRight, int keyJump, int keyMoveUp, int keyMoveDown);
	void handleKeyEvent(int key, bool bIsPressed);
	void horizontalMove(MoveState moveState);
	void verticalMove(MoveState moveState);
	void calculateMove();
	void jump();
	void land();
	void stopMove(MoveState moveState);
	void die();
	bool isDied() { return died; };
};
#pragma once
#include <iostream>
#include "GameManager/ResourceManagers.h"
#include "Actor.h"
#include "SpriteAnimation.h"

class Texture;

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
	MoveState	moveState;
	JumpState	jumpState;
	float		velocityScale;
	float		totalTime;
	bool		playing;

	std::shared_ptr<SpriteAnimation> IDLE_Left_Animation;
	std::shared_ptr<SpriteAnimation> IDLE_Right_Animation;
	std::shared_ptr<SpriteAnimation> moveLeft_Animation;
	std::shared_ptr<SpriteAnimation> moveRight_Animation;
public:
	Player();
	~Player();

	void init() override;
	void update(float deltaTime) override;
	void draw() override;

	void moveRight();
	void horizontalMove(MoveState moveState, float velocityScale);
	void stopMove();

	void setCategory(Category category) override;
};
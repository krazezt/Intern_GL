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

	std::shared_ptr<SpriteAnimation> IDLE_Animation;
	std::shared_ptr<SpriteAnimation> move_Animation;
public:
	Player();
	~Player();

	void init() override;
	void update(float deltaTime) override;
	void draw() override;

	virtual void initCollisionBox(float x_location, float y_location, float width, float height);

	void moveRight();
	void horizontalMove(MoveState moveState, float velocityScale);
	void stopMove();

	void setCategory(Category category) override;
};
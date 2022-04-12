#pragma once
#include <iostream>
#include "Actor.h"
#include "Player.h"
#include "SpriteAnimation.h"

class Texture;

class TriggerBlock : public Actor {
private:
	MoveState	moveState;
	float		velocityScale;
public:
	TriggerBlock();
	~TriggerBlock();

	void init(float x_location, float y_location) override;
	void update(float deltaTime) override;
	void draw() override;

	virtual void initCollisionBox(float x_location, float y_location, float width, float height);
	void consumeCollision() override;
};
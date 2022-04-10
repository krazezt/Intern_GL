#pragma once
#include <iostream>
#include "Actor.h"
#include "Player.h"
#include "SpriteAnimation.h"

class Texture;

class NumberBlock : public Actor {
private:
	int		value;
	bool	isTriggering;
public:
	NumberBlock();
	~NumberBlock();

	void init(float x_location, float y_location) override;
	void update(float deltaTime) override;
	void draw() override;

	virtual void	initCollisionBox(float x_location, float y_location, float width, float height);
	void			consumeCollision() override;

	void	setValue(int newValue) { this->value = newValue; };
	int		getValue() { return this->value; };
	bool	checkTriggering() { return this->isTriggering; };
};
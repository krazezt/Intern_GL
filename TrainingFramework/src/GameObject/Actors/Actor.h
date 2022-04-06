#pragma once
#include <iostream>
#include "ObjectType/Category.h"
#include "Collision/CollisionBox2D.h"
#include "ObjectType/Collidable.h"
#include "GameManager/ResourceManagers.h"
#include "SpriteAnimation.h"

class SpriteAnimation;

class Actor : public Collidable {
protected:
	std::shared_ptr<SpriteAnimation> animation;
	int movement_speed;
	int width, height;

public:
	void setLocation(float location_X, float location_Y);
	float getLocationX();
	float getLocationY();

	void	setCategory(Category category) { this->category = category; };

	virtual void	init(float x_location, float y_location) = 0;
	virtual void	update(float deltaTime) = 0;
	virtual void	draw() = 0;

	virtual	void	consumeCollision();
};
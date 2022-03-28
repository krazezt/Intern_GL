#pragma once
#include <iostream>
#include "ObjectType/Category.h"
#include "Collision/CollisionBox2D.h"
#include "ObjectType/Collidable.h"

class SpriteAnimation;

class Actor : public Collidable {
protected:
	std::shared_ptr<SpriteAnimation> animation;
	float x_location;
	float y_location;
	int movement_speed;
	
	Category	category;
public:
	void setLocation(float location_X, float location_Y);
	float getLocationX();
	float getLocationY();

	virtual void setCategory(Category category) = 0;
	Category getCategory() { return category; };

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
};
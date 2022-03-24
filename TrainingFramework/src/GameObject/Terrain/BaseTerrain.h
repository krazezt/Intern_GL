#pragma once
#include "Sprite2D.h"
#include "ObjectType/Category.h"
#include "CollisionBox2D.h"

class BaseTerrain {
protected:
	float x_location;
	float y_location;
	Category category;

	std::shared_ptr<Sprite2D>	sprite2D;
	std::shared_ptr<CollisionBox2D>	collisionBox;
public:
	BaseTerrain();
	~BaseTerrain();

	void update(float deltaTime);
	void draw();

	virtual void init(float x_location, float y_location) = 0;
};
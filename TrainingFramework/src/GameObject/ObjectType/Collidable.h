#pragma once
#include "Collision/CollisionBox2D.h"


class Collidable {
protected:
	std::shared_ptr<CollisionBox2D>	collisionBox;

public:
	virtual void initCollisionBox(float x_location, float y_location, float width, float height) = 0;
	std::shared_ptr<CollisionBox2D>	getCollisionBox() { return collisionBox; };
};
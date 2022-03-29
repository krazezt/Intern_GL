#pragma once
#include "Sprite2D.h"
#include "ObjectType/Category.h"
#include "ObjectType/Collidable.h"
#include "Collision/CollisionBox2D.h"

class BaseTerrain : public Collidable {
protected:
	std::shared_ptr<Sprite2D>	sprite2D;
public:
	BaseTerrain();
	~BaseTerrain();

	virtual void	update(float deltaTime);
	virtual void	draw();

	virtual void	init(float x_location, float y_location) = 0;
	virtual void	setLocation(float x_location, float y_location) = 0;

	virtual void	consumeCollision();
};
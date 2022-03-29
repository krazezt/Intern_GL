#pragma once
#include <list>

#include "Collision/Collision.h"
#include "Collision/CollisionBox2D.h"
#include "CollisionManager.h"
#include "BaseGameObject.h"

enum class CollisionDetail {
	IGNORED = 0,

	OVERLAP_LEFT,
	OVERLAP_BOTTOM,
	OVERLAP_RIGHT,
	OVERLAP_TOP,

	BLOCK_LEFT,
	BLOCK_BOTTOM,
	BLOCK_RIGHT,
	BLOCK_TOP,
};

typedef struct _collisionInfo {
	Collision		collisionType;
	CollisionDetail	collisionDetail;
	Vector2			collideVector;
	Category		collideObjCategory;
} CollisionInfo;

class Collidable : public BaseGameObject {
protected:
	std::shared_ptr<CollisionBox2D>	collisionBox;
	std::list<std::shared_ptr<CollisionInfo>> list_CollisionInfo;
	Category	category;
	float		prev_deltaTime;

public:
	virtual void	initCollisionBox(float x_location, float y_location, float width, float height) = 0;
	virtual void	applyCollision(std::shared_ptr<Collidable> collideObj);
	virtual void	consumeCollision() = 0;
	Category		getCategory() { return category; };
	std::shared_ptr<CollisionBox2D>	getCollisionBox() { return collisionBox; };
};
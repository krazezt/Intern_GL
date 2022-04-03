#pragma once
#include <list>

#include "Collision/Collision.h"
#include "Collision/CollisionBox2D.h"
#include "CollisionManager.h"
#include "BaseGameObject.h"

enum class CollideDirection {
	TOP,
	LEFT,
	BOTTOM,
	RIGHT,
};

typedef struct _collisionInfo {
	Collision			collisionType;
	CollideDirection	collideDirection;
	Vector2				collideVector;
	Category			collideObjCategory;
	float				blockCoordinate;
} CollisionInfo;

typedef struct _blockInfo {
	float	blockCoordinate;
	bool	isBlocking;
} BlockInfo;

typedef struct _blockState {
	BlockInfo	top;
	BlockInfo	left;
	BlockInfo	bottom;
	BlockInfo	right;

	void reset() {
		top.isBlocking = false;
		left.isBlocking = false;
		bottom.isBlocking = false;
		right.isBlocking = false;
	};
} BlockState;

class Collidable : public BaseGameObject {
protected:
	std::shared_ptr<CollisionBox2D>	collisionBox;
	std::list<std::shared_ptr<CollisionInfo>> list_CollisionInfo;
	BlockState	blockState;
	Category	category;
	float		prev_deltaTime;

public:
	virtual void	initCollisionBox(float x_location, float y_location, float width, float height) = 0;
	virtual void	applyCollision(std::shared_ptr<Collidable> collideObj);
	virtual void	consumeCollision() = 0;
	Category		getCategory() { return category; };
	std::shared_ptr<CollisionBox2D>	getCollisionBox() { return collisionBox; };
};
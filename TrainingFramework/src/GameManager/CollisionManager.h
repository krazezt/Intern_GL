#pragma once
#include <iostream>
#include <list>
#include "Singleton.h"
#include "Collision/Collision.h"
#include "ObjectType/Category.h"

class CollisionManager : public CSingleton<CollisionManager> {
private:
	std::list<std::shared_ptr<CollisionInteractive>> list_collisionInteractive;

	void	addCollisionInteractive(Category category1, Category category2, Collision interactive);
public:
	CollisionManager();
	~CollisionManager();

	void		init();
	Collision	getCollisionInteractive(Category category1, Category category2);
};
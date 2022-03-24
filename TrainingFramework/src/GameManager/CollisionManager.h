#pragma once
#include <iostream>
#include <list>
#include "Singleton.h"
#include "ObjectType/Collision.h"
#include "ObjectType/Category.h"

class CollisionManager : public CSingleton<CollisionManager> {
private:
	CollisionManager();
	~CollisionManager();

	std::list<std::shared_ptr<CollisionInteractive>> list_collisionInteractive;

	void	addCollisionInteractive(Category category1, Category category2, Collision interactive);
public:
	void		init();
	Collision	getCollisionInteractive(Category category1, Category category2);
};
#pragma once
#include <iostream>
#include "ObjectType/Category.h"

enum class Collision {
	IGNORE = 0,
	OVERLAP,
	BLOCK,
};

class CollisionInteractive {
private:
	Category	category_1;
	Category	category_2;
	Collision	interactive;
public:
	void		init(Category& category1, Category& category2, Collision& interactive);
	bool		checkCategory(Category category1, Category category2);
	Collision	getCollisionType() { return interactive; };
};
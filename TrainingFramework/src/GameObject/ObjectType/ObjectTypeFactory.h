#pragma once
#include "Category.h"
#include "Collision.h"

class ObjectTypeFactory {
public:
	std::shared_ptr<Category>	createCategory(Category category);
	std::shared_ptr<Collision>	createCollisionType(Collision collision);
};
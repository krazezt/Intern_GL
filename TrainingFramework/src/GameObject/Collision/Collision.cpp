#include "Collision.h"

void CollisionInteractive::init(Category& category1, Category& category2, Collision& interactive) {
	this->category_1 = category1;
	this->category_2 = category2;
	this->interactive = interactive;
};

bool CollisionInteractive::checkCategory(Category category1, Category category2) {
	return (
		(this->category_1 == category1 && this->category_2 == category2) ||
		(this->category_1 == category2 && this->category_2 == category1)
		) ? true : false;
};
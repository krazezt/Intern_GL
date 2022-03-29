#include "BaseTerrain.h"

BaseTerrain::BaseTerrain() {
	this->category = Category::TERRAIN;
};

BaseTerrain::~BaseTerrain() {};

void BaseTerrain::update(float deltaTime) {
	this->setLocation(x_location + velocityVector.x * deltaTime, y_location + velocityVector.y * deltaTime);
	this->sprite2D->Update(deltaTime);
	this->collisionBox->update(deltaTime);
};

void BaseTerrain::draw() {
	this->sprite2D->Draw();
	this->collisionBox->draw();
};

void BaseTerrain::consumeCollision() {};
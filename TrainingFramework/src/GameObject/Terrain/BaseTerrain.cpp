#include "BaseTerrain.h"

BaseTerrain::BaseTerrain() {
	this->category = Category::TERRAIN;
};

BaseTerrain::~BaseTerrain() {};

void BaseTerrain::update(float deltaTime) {
	this->sprite2D->Update(deltaTime);
	this->collisionBox->update(deltaTime);
};

void BaseTerrain::draw() {
	this->sprite2D->Draw();
	this->collisionBox->draw();
};
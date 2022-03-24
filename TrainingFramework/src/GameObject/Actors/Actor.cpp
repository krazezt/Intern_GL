#include "Actor.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteAnimation.h"

void Actor::setLocation(float location_X, float location_Y) {
	this->x_location = location_X;
	this->y_location = location_Y;
	animation->Set2DPosition(this->x_location, this->y_location);
	collisionBox->setLocation(this->x_location, this->y_location);
}

float Actor::getLocationX() {
	return this->x_location;
}

float Actor::getLocationY() {
	return this->y_location;
}
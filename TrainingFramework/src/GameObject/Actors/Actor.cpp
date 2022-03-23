#include "Actor.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteAnimation.h"

void Actor::setLocation(int location_X, int location_Y) {
	this->x_location = location_X;
	this->y_location = location_Y;
	animation->Set2DPosition(this->x_location, this->y_location);
}

int Actor::getLocationX() {
	return this->x_location;
}

int Actor::getLocationY() {
	return this->y_location;
}
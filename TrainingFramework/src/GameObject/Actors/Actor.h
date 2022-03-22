#pragma once
#include <iostream>

class SpriteAnimation;

class Actor {
protected:
	std::shared_ptr<SpriteAnimation> animation;
	int x_location;
	int y_location;
	int movement_speed;
public:
	void setLocation(int location_X, int location_Y);
	int getLocationX();
	int getLocationY();

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
};
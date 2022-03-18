#pragma once
#include <iostream>
#include "GameManager/ResourceManagers.h"

class SpriteAnimation;

class Player {
private:
	std::shared_ptr<SpriteAnimation> animation;
	int x_location;
	int y_location;
public:
	void init();
	void setAnimation(std::shared_ptr<SpriteAnimation> spriteAnimation);
	void setLocation(int location_X, int location_Y);
	void show();
};
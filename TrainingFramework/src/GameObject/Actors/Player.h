#pragma once
#include <iostream>
#include "GameManager/ResourceManagers.h"
#include "Actor.h"

class SpriteAnimation;

class Player : public Actor {
public:
	void init() override;
	void update(float deltaTime) override;
	void draw() override;
};
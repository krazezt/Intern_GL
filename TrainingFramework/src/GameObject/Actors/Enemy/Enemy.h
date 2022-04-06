#pragma once
#include <iostream>
#include "Actors/Actor.h"

class Enemy : public Actor {
	public:
		Enemy();
		~Enemy();

		virtual void init(float x_location, float y_location)	= 0;
		virtual void update(float deltaTime) = 0;
		virtual void draw() = 0;
};
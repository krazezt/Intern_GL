#pragma once
#include "Enemy.h"

class Enemy1 : public Enemy {
	private:
		float	m_totalTime;
		bool	bulletLoading;
	public:
		Enemy1();
		~Enemy1();

		void initCollisionBox(float x_location, float y_location, float width, float height) override;

		void init(float x_location, float y_location) override;
		void update(float deltaTime) override;
		void draw() override;
		void consumeCollision() override {};
};
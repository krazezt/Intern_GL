#pragma once
#include "Enemy.h"

class Enemy2 : public Enemy {
private:
	float	m_totalTime;
	bool	bulletLoading;
	bool	flyingUp, movingRight;
	float	init_x;
	float	init_y;
public:
	Enemy2();
	~Enemy2();

	void initCollisionBox(float x_location, float y_location, float width, float height) override;

	void init(float x_location, float y_location) override;
	void update(float deltaTime) override;
	void draw() override;
	void consumeCollision() override {};
};
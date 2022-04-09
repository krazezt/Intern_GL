#pragma once
#include "GameObject/Actors/Actor.h"

class EnemyBullet2 : public Actor {
private:
	float totalTime;
protected:
public:
	EnemyBullet2();
	~EnemyBullet2();

	void initCollisionBox(float x_location, float y_location, float width, float height) override;

	void init(float x_location, float y_location) override;
	void update(float deltaTime) override;
	void draw() override;
	void consumeCollision() override {};
};
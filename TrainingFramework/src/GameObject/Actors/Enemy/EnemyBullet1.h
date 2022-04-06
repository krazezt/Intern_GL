#pragma once
#include "GameObject/Actors/Actor.h"

class EnemyBullet1 : public Actor {
	private:
	protected:
	public:
		EnemyBullet1();
		~EnemyBullet1();

		void initCollisionBox(float x_location, float y_location, float width, float height) override;

		void init(float x_location, float y_location) override;
		void update(float deltaTime) override;
		void draw() override;
		void consumeCollision() override {};
};
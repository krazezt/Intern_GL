#include "EnemyBullet2.h"

EnemyBullet2::EnemyBullet2() {
	this->category = Category::ENEMY_BULLET;
};

EnemyBullet2::~EnemyBullet2() {}

void EnemyBullet2::init(float x_location, float y_location) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("EnemyBullet2.tga");

	width = 38;
	height = 30;

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 3, 1, 0, 0.1f);
	animation->SetSize(width, height);

	this->initCollisionBox(this->x_location, this->y_location, width, height);
	this->velocityVector = Vector2(0.0f, 400.0f);
	this->blockState.reset();

	this->setLocation(x_location, y_location);
}

void EnemyBullet2::initCollisionBox(float x_location, float y_location, float width, float height) {
	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, width, height);
}

void EnemyBullet2::update(float deltaTime) {
	totalTime += deltaTime;
	this->setLocation(x_location + this->velocityVector.x * deltaTime, y_location + this->velocityVector.y * deltaTime);
	this->animation->Update(deltaTime);
	this->collisionBox->update(deltaTime);
}

void EnemyBullet2::draw() {
	this->animation->Draw();
	this->collisionBox->draw();
}
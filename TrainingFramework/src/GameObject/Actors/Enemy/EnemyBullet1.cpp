#include "EnemyBullet1.h"
#include "GameStates//GSPlay.h"

EnemyBullet1::EnemyBullet1() {
	this->category = Category::ENEMY_BULLET;
};

EnemyBullet1::~EnemyBullet1() {}

void EnemyBullet1::init(float x_location, float y_location) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("EnemyBullet1.tga");

	width = 38;
	height = 47;

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 4, 1, 0, 0.1f);
	animation->SetSize(width, height);

	this->initCollisionBox(this->x_location, this->y_location, width, height);
	this->velocityVector = Vector2(0.0f, 400.0f);
	this->blockState.reset();

	this->setLocation(x_location, y_location);
}

void EnemyBullet1::initCollisionBox(float x_location, float y_location, float width, float height) {
	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, width, height);
}

void EnemyBullet1::update(float deltaTime) {
	totalTime += deltaTime;
	this->setLocation(x_location + this->velocityVector.x * deltaTime, y_location + this->velocityVector.y * deltaTime);
	this->animation->Update(deltaTime);
	this->collisionBox->update(deltaTime);
}

void EnemyBullet1::draw() {
	this->animation->Draw();
	this->collisionBox->draw();
}
#include "Enemy2.h"
#include "EnemyBullet2.h"
#include "GameStates/GSPlaySurvive.h"

Enemy2::Enemy2() {
	this->category = Category::ENEMY;
}

Enemy2::~Enemy2() {}

void Enemy2::init(float x_location, float y_location) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy2.tga");

	init_x = x_location;
	init_y = y_location;
	flyingUp = true;
	movingRight = false;
	width = Globals::screenWidth / 12.8f;
	height = Globals::screenWidth / 12.8f;
	bulletLoading = true;
	m_totalTime = 0.0f;

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 9, 1, 0, 0.1f);
	animation->SetSize(width, height);

	this->initCollisionBox(this->x_location, this->y_location, width, height);
	this->velocityVector = Vector2(Globals::screenWidth / 6, Globals::screenWidth / 6);
	this->blockState.reset();

	this->setLocation(x_location, y_location);
}

void Enemy2::initCollisionBox(float x_location, float y_location, float width, float height) {
	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, width/1.5f, height/1.5f);
}

void Enemy2::update(float deltaTime) {
	if (y_location - height <= 0 || y_location + height >= Globals::screenHeight) flyingUp = !flyingUp;
	if (x_location - width <= 0 || x_location + width >= Globals::screenWidth) {
		this->animation->SetRotation(Vector3(0.0f, PI * (movingRight ? 0 : 1), 0.0f));
		movingRight = !movingRight;
	}

	m_totalTime += deltaTime;
	if (
		((((int)(m_totalTime / 0.1f)) % 9) >= 7) &&
		(bulletLoading == false)
		) {
		bulletLoading = true;
		std::shared_ptr<EnemyBullet2> newBullet = std::make_shared<EnemyBullet2>();
		newBullet->init(this->x_location, this->y_location + 80);
		GSPlaySurvive::addSpawnedActor(newBullet);
	}
	else if (
		((((int)(m_totalTime / 0.1f)) % 9) < 7) &&
		(bulletLoading == true)
		) {
		bulletLoading = false;
	}

	this->setLocation(x_location + this->velocityVector.x * deltaTime * (movingRight ? 1 : -1), y_location + this->velocityVector.y * deltaTime * (flyingUp ? -1 : 1));

	this->animation->Update(deltaTime);
	this->collisionBox->update(deltaTime);
}

void Enemy2::draw() {
	this->animation->Draw();
	this->collisionBox->draw();
}
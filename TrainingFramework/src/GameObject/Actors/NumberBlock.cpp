#include "NumberBlock.h"
#include "Shader.h"
#include "Texture.h"

NumberBlock::NumberBlock() {
	category = Category::TRIGGER_BLOCK;
}
NumberBlock::~NumberBlock() {}

void NumberBlock::init(float x_location, float y_location) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("NumberBlock.tga");

	width = 100;
	height = 100;
	movement_speed = 0;
	prev_deltaTime = 0;
	value = 0;
	isTriggering = false;

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 1, 0, 1.0f);
	animation->SetSize(width, height);

	this->initCollisionBox(x_location, y_location, width, height);
	this->velocityVector = Vector2(0.0f, 0.0f);
	this->blockState.reset();

	this->setLocation(x_location, y_location);
}

void NumberBlock::initCollisionBox(float x_location, float y_location, float width, float height) {
	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, width, height);
}

void NumberBlock::update(float deltaTime) {
	if (!this->list_CollisionInfo.empty()) {
		this->consumeCollision();
	}

	this->setLocation(x_location + velocityVector.x * deltaTime, y_location + velocityVector.y * deltaTime);

	this->animation->Update(deltaTime);
	this->collisionBox->update(deltaTime);
	this->prev_deltaTime = deltaTime;
}

void NumberBlock::draw() {
	this->animation->Draw();
	this->collisionBox->draw();
}

void NumberBlock::consumeCollision() {
	if (list_CollisionInfo.empty() && isTriggering) {
		isTriggering = false;
		// TODO
	}

	while (!list_CollisionInfo.empty()) {
		switch (list_CollisionInfo.front()->collisionType) {
		case Collision::IGNORED:
			break;
		case Collision::BLOCK:
			break;
		case Collision::OVERLAP:
			if (!isTriggering) {
				switch (list_CollisionInfo.front()->collideObjCategory) {
					case Category::PLAYER:
						isTriggering = true;
						// TODO
						break;
					default:
						break;
				}
			}
			break;
		default:
			break;
		}

		list_CollisionInfo.pop_front();
	}
}
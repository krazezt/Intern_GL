#include "TriggerBlock.h"
#include "Shader.h"
#include "Texture.h"

TriggerBlock::TriggerBlock() {
	category = Category::TRIGGER_BLOCK;
}
TriggerBlock::~TriggerBlock() {}

void TriggerBlock::init(float x_location, float y_location) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("TriggerBlock.tga");

	width = 70;
	height = 70;
	movement_speed = 350;
	velocityScale = 1;
	prev_deltaTime = 0;

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 1, 0, 1.0f);
	animation->SetSize(width, height);

	this->initCollisionBox(x_location, y_location, width, height);
	this->velocityVector = Vector2(0.0f, 0.0f);
	this->blockState.reset();

	this->setLocation(x_location, y_location);
}

void TriggerBlock::initCollisionBox(float x_location, float y_location, float width, float height) {
	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, width, height);
}

void TriggerBlock::update(float deltaTime) {

	if (!this->list_CollisionInfo.empty()) {
		this->consumeCollision();
	}

	this->setLocation(x_location + velocityScale * velocityVector.x * deltaTime, y_location + velocityScale * velocityVector.y * deltaTime);

	if (this->blockState.top.isBlocking && this->y_location < this->blockState.top.blockCoordinate + this->collisionBox->getHeight() / 2)
		this->setLocation(x_location, this->blockState.top.blockCoordinate + this->collisionBox->getHeight() / 2);

	if (this->blockState.right.isBlocking && this->x_location > this->blockState.right.blockCoordinate - this->collisionBox->getWidth() / 2)
		this->setLocation(this->blockState.right.blockCoordinate - this->collisionBox->getWidth() / 2, y_location);

	if (this->blockState.left.isBlocking && this->x_location < this->blockState.left.blockCoordinate + this->collisionBox->getWidth() / 2)
		this->setLocation(this->blockState.left.blockCoordinate + this->collisionBox->getWidth() / 2, y_location);

	if (this->blockState.bottom.isBlocking && this->y_location > this->blockState.bottom.blockCoordinate - this->collisionBox->getHeight() / 2)
		this->setLocation(x_location, this->blockState.bottom.blockCoordinate - this->collisionBox->getHeight() / 2);

	this->animation->Update(deltaTime);
	this->collisionBox->update(deltaTime);
	this->prev_deltaTime = deltaTime;
	this->blockState.reset();
}

void TriggerBlock::draw() {
	this->animation->Draw();
	this->collisionBox->draw();
}

void TriggerBlock::horizontalMove(MoveState moveState) {

	switch (this->moveState) {
	case MoveState::MOVE_RIGHT:
		this->velocityVector.x = movement_speed;
		this->animation->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
		break;
	case MoveState::MOVE_LEFT:
		this->velocityVector.x = -1 * movement_speed;
		this->animation->SetRotation(Vector3(0.0f, PI, 0.0f));
		break;
	default:
		break;
	}
}

void TriggerBlock::verticalMove(MoveState moveState) {
	this->moveState = moveState;

	switch (this->moveState) {
	case MoveState::MOVE_UP:
		this->velocityVector.y = -1 * movement_speed;
		break;
	case MoveState::MOVE_DOWN:
		this->velocityVector.y = movement_speed;
		break;
	default:
		break;
	}
}

void TriggerBlock::consumeCollision() {
	while (!list_CollisionInfo.empty()) {
		switch (list_CollisionInfo.front()->collisionType) {
		case Collision::IGNORED:
			break;
		case Collision::BLOCK:
			break;
		case Collision::OVERLAP:
			switch (list_CollisionInfo.front()->collideDirection) {
				case CollideDirection::LEFT:
					this->blockState.left.isBlocking = true;
					this->blockState.left.blockCoordinate = list_CollisionInfo.front()->blockCoordinate;
					this->velocityVector = Vector2(movement_speed, 0.0f);
					break;
				case CollideDirection::RIGHT:
					this->blockState.right.isBlocking = true;
					this->blockState.right.blockCoordinate = list_CollisionInfo.front()->blockCoordinate;
					this->velocityVector = Vector2(-1 * movement_speed, 0.0f);
					break;
				case CollideDirection::TOP:
					this->blockState.top.isBlocking = true;
					this->blockState.top.blockCoordinate = list_CollisionInfo.front()->blockCoordinate;
					this->velocityVector = Vector2(0.0f, movement_speed);
					break;
				case CollideDirection::BOTTOM:
					this->blockState.bottom.isBlocking = true;
					this->blockState.bottom.blockCoordinate = list_CollisionInfo.front()->blockCoordinate;
					this->velocityVector = Vector2(0.0f, -1 * movement_speed);
					break;
				default:
					break;
			}
		default:
			break;
		}

		list_CollisionInfo.pop_front();
	}
}
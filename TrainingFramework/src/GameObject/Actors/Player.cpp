#include "Player.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteAnimation.h"

Player::Player() {}
Player::~Player() {}

void Player::init() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation_Start.tga");

	int width = 150, height = 100;

	movement_speed = 350;
	velocityScale = 1;
	totalTime = 0;
	playing = false;
	category = Category::PLAYER;
	prev_deltaTime = 0;
	jumpState = JumpState::LANDING;
	jumpSpeed = 1500;

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 7, 1, 0, 0.2f);
	animation->SetSize(width, height);

	texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation_IDLE_Right.tga");
	IDLE_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 3, 1, 0, 0.5f);
	IDLE_Animation->SetSize(width, height);

	texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation_MoveRight.tga");
	move_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 1, 0, 0.075f);
	move_Animation->SetSize(width, height);

	texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation_Jump.tga");
	jump_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 1, 0, 1.0f);
	jump_Animation->SetSize(width*9/8, height);

	this->initCollisionBox(this->x_location, this->y_location, width, height);
	this->velocityVector = Vector2(0.0f, 150.0f);
	this->blockState.reset();

	this->setLocation(1000, 420);
}

void Player::initCollisionBox(float x_location, float y_location, float width, float height) {
	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, width, height);
}

void Player::update(float deltaTime) {
	totalTime += deltaTime;
	if (totalTime > 1.0f && playing == false) {
		this->animation = IDLE_Animation;
		this->setLocation(x_location, y_location);
		playing = true;
	}

	if (!this->list_CollisionInfo.empty()) {
		this->consumeCollision();
	}

	if (this->jumpState != JumpState::LANDING) {
		this->velocityVector.y += deltaTime * GRAVITY;
		if (this->velocityVector.y > 0) this->jumpState = JumpState::FALLING;
	}
	else if (!this->blockState.bottom.isBlocking) this->jumpState = JumpState::FALLING;

	float prev_x = x_location, prev_y = y_location;
	this->setLocation(x_location + velocityScale * velocityVector.x * deltaTime, y_location + velocityScale * velocityVector.y * deltaTime);

	if (this->blockState.top.isBlocking && this->y_location < prev_y) this->setLocation(x_location, this->blockState.top.blockCoordinate + this->collisionBox->getHeight() / 2);
	if (this->blockState.right.isBlocking && this->x_location > prev_x) this->setLocation(this->blockState.right.blockCoordinate - this->collisionBox->getWidth() / 2, y_location);
	if (this->blockState.left.isBlocking && this->x_location <= prev_x) this->setLocation(this->blockState.left.blockCoordinate + this->collisionBox->getWidth() / 2, y_location);
	if (this->blockState.bottom.isBlocking && this->y_location >= prev_y) this->setLocation(x_location, this->blockState.bottom.blockCoordinate - this->collisionBox->getHeight() / 2);

	this->animation->Update(deltaTime);
	this->collisionBox->update(deltaTime);
	this->prev_deltaTime = deltaTime;
	this->blockState.reset();
}

void Player::draw() {
	this->animation->Draw();
	this->collisionBox->draw();
}

void Player::stopMove() {
	this->animation = IDLE_Animation;
	if (this->moveState == MoveState::MOVE_RIGHT)
		this->animation->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
	else this->animation->SetRotation(Vector3(0.0f, PI, 0.0f));
	this->moveState = MoveState::IDLE;
	this->velocityVector.x = 0;

	this->setLocation(x_location, y_location);
}

void Player::horizontalMove(MoveState moveState) {
	if (!playing) return;
	this->moveState = moveState;
	this->animation = move_Animation;

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

void Player::land() {
	this->jumpState = JumpState::LANDING;
	this->velocityVector.y = 0;
}

void Player::jump() {
	if (!playing) return;
	if (this->jumpState == JumpState::LANDING) {
		this->velocityVector.y = -jumpSpeed;
		this->jumpState = JumpState::JUMPING;
		this->setLocation(x_location, y_location + 0.1f);
	}
	else return;
}

void Player::setCategory(Category category) {
	this->category = category;
}
void Player::consumeCollision() {
	while (!list_CollisionInfo.empty()) {
		switch (list_CollisionInfo.front()->collisionType) {
			case Collision::IGNORED:
				break;
			case Collision::OVERLAP:
				break;
			case Collision::BLOCK:
				switch (list_CollisionInfo.front()->collideDirection) {
					case CollideDirection::LEFT:
						this->blockState.left.isBlocking = true;
						this->blockState.left.blockCoordinate = list_CollisionInfo.front()->blockCoordinate;
						break;
					case CollideDirection::RIGHT:
						this->blockState.right.isBlocking = true;
						this->blockState.right.blockCoordinate = list_CollisionInfo.front()->blockCoordinate;
						break;
					case CollideDirection::TOP:
						this->blockState.top.isBlocking = true;
						this->blockState.top.blockCoordinate = list_CollisionInfo.front()->blockCoordinate;
						this->velocityVector.y = 100.0f;
						break;
					case CollideDirection::BOTTOM:
						if (this->jumpState == JumpState::FALLING && list_CollisionInfo.front()->collideObjCategory == Category::TERRAIN) {
							this->land();
						}
						this->blockState.bottom.isBlocking = true;
						this->blockState.bottom.blockCoordinate = list_CollisionInfo.front()->blockCoordinate;
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
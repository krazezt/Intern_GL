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
	jumpState = JumpState::JUMPING;

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
	this->velocityVector = Vector2(0.0f, 0.0f);

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

	if (this->jumpState == JumpState::JUMPING) {
		this->velocityVector.y += deltaTime * GRAVITY;
	}
	/*this->setLocation(x_location, y_location);*/
	this->setLocation(x_location + velocityScale * velocityVector.x * deltaTime, y_location + velocityScale * velocityVector.y * deltaTime);
	this->animation->Update(deltaTime);
	this->collisionBox->update(deltaTime);
	this->prev_deltaTime = deltaTime;
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
	this->moveState = moveState;
	if (this->jumpState == JumpState::LANDING) this->animation = move_Animation;

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
	this->velocityVector.y = 20.0f;
}

void Player::jump() {
	if (this->jumpState == JumpState::LANDING) {
		this->velocityVector.y = -500;
		this->jumpState = JumpState::JUMPING;
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
					case CollideDirection::RIGHT:
						if (jumpState != JumpState::LANDING)
							this->setLocation(
								x_location - list_CollisionInfo.front()->collideVector.x * prev_deltaTime,
								y_location - list_CollisionInfo.front()->collideVector.y * prev_deltaTime
							);
						else 
							this->setLocation(
								x_location + list_CollisionInfo.front()->collideVector.x * prev_deltaTime,
								y_location - list_CollisionInfo.front()->collideVector.y * prev_deltaTime
							);
						break;
					case CollideDirection::TOP:
						break;
					case CollideDirection::BOTTOM:
						if (list_CollisionInfo.front()->collideObjCategory == Category::TERRAIN) {
							this->land();
							y_location -= list_CollisionInfo.front()->collideVector.y * prev_deltaTime;
						}
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
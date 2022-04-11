#include "Player.h"
#include "Shader.h"
#include "Texture.h"

Player::Player() {}
Player::~Player() {}

void Player::init(float x_location, float y_location) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation_Start.tga");

	width = 120;
	height = 90;
	movement_speed = 350;
	velocityScale = 1;
	totalTime = 0;
	playing = false;
	category = Category::PLAYER;
	prev_deltaTime = 0;
	jumpState = JumpState::LANDING;
	jumpSpeed = 1500;
	died = false;
	dying = false;

	keyMoveLeft = -1;
	keyMoveRight = -1;
	keyJump = -1;
	keyMoveUp = -1;
	keyMoveDown = -1;

	movingUp = false;
	movingDown = false;
	movingLeft = false;
	movingRight = false;

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

	this->initCollisionBox(this->x_location, this->y_location, width/1.5f, height);
	this->velocityVector = Vector2(0.0f, 0.0f);
	this->blockState.reset();

	this->setLocation(x_location, y_location);
}

void Player::initCollisionBox(float x_location, float y_location, float width, float height) {
	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, width, height);
}

void Player::update(float deltaTime) {
	if (died) return;

	totalTime += deltaTime;
	dieTime = dying ? dieTime : totalTime;

	if (totalTime - dieTime >= 2.2f) {
		died = true;
	}
	
	if (totalTime > 1.0f && playing == false) {
		this->animation = IDLE_Animation;
		this->setLocation(x_location, y_location);
		playing = true;
	}

	if (!this->list_CollisionInfo.empty()) {
		this->consumeCollision();
	}

	if (this->jumpState != JumpState::LANDING) {
		this->velocityVector.y += deltaTime * Globals::gravity;
		if (this->velocityVector.y > 0) this->jumpState = JumpState::FALLING;
	}
	else if (!this->blockState.bottom.isBlocking) this->jumpState = JumpState::FALLING;

	float prev_x = x_location, prev_y = y_location;
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

void Player::draw() {
	if (died) return;
	this->animation->Draw();
	this->collisionBox->draw();
}

void Player::bindKeys(int keyMoveLeft, int keyMoveRight, int keyJump, int keyMoveUp, int keyMoveDown) {
	this->keyMoveLeft = keyMoveLeft;
	this->keyMoveRight = keyMoveRight;
	this->keyJump = keyJump;
	this->keyMoveUp = keyMoveUp;
	this->keyMoveDown = keyMoveDown;
};

void Player::handleKeyEvent(int key, bool bIsPressed) {
	if (key == keyMoveRight)
		bIsPressed ? this->horizontalMove(MoveState::MOVE_RIGHT) : this->stopMove(MoveState::MOVE_RIGHT);
	else if (key == keyMoveLeft)
		bIsPressed ? this->horizontalMove(MoveState::MOVE_LEFT) : this->stopMove(MoveState::MOVE_LEFT);
	else if (key == keyJump)
		bIsPressed ? this->jump() : NULL;
	else if (key == keyMoveUp)
		bIsPressed ? this->verticalMove(MoveState::MOVE_UP) : this->stopMove(MoveState::MOVE_UP);
	else if (key == keyMoveDown)
		bIsPressed ? this->verticalMove(MoveState::MOVE_DOWN) : this->stopMove(MoveState::MOVE_DOWN);
}

void Player::stopMove(MoveState moveState) {
	if (!playing || died || dying) return;
	
	switch (moveState) {
		case MoveState::MOVE_RIGHT:
			movingRight = false;
			IDLE_Animation->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			this->velocityVector.x = 0;
			break;
		case MoveState::MOVE_LEFT:
			movingLeft = false;
			IDLE_Animation->SetRotation(Vector3(0.0f, PI, 0.0f));
			this->velocityVector.x = 0;
			break;
		case MoveState::MOVE_DOWN:
			movingDown = false;
			this->velocityVector.y = 0;
			break;
		case MoveState::MOVE_UP:
			movingUp = false;
			this->velocityVector.y = 0;
			break;
		default:
			break;
	}

	if (!movingLeft && !movingRight && !movingUp && !movingDown) this->animation = IDLE_Animation;

	this->moveState = MoveState::IDLE;

	this->setLocation(x_location, y_location);
}

void Player::horizontalMove(MoveState moveState) {
	if (!playing || died || dying) return;
	this->moveState = moveState;
	this->animation = move_Animation;

	switch (this->moveState) {
		case MoveState::MOVE_RIGHT:
			this->velocityVector.x = movement_speed;
			this->movingRight = true;
			this->animation->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			break;
		case MoveState::MOVE_LEFT:
			this->velocityVector.x = -1 * movement_speed;
			this->movingLeft = true;
			this->animation->SetRotation(Vector3(0.0f, PI, 0.0f));
			break;
		default:
			break;
	}
}

void Player::verticalMove(MoveState moveState) {
	if (!playing || died || dying) return;
	this->moveState = moveState;
	this->animation = move_Animation;

	switch (this->moveState) {
		case MoveState::MOVE_UP:
			this->velocityVector.y = -1 * movement_speed;
			this->movingUp = true;
			break;
		case MoveState::MOVE_DOWN:
			this->velocityVector.y = movement_speed;
			this->movingDown = true;
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
	if (!playing || died || dying) return;
	if (this->jumpState == JumpState::LANDING) {
		this->velocityVector.y = -jumpSpeed;
		this->jumpState = JumpState::JUMPING;
		this->setLocation(x_location, y_location + 0.1f);
	}
	else return;
}

void Player::calculateMove() {

}

void Player::consumeCollision() {
	while (!list_CollisionInfo.empty()) {
		switch (list_CollisionInfo.front()->collisionType) {
			case Collision::IGNORED:
				break;
			case Collision::OVERLAP:
				switch (list_CollisionInfo.front()->collideObjCategory)
				{
					case Category::ENEMY:
					case Category::ENEMY_BULLET:
						this->die();
						break;
					default:
						break;
				}
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
						this->setLocation(x_location, y_location + 0.1f);
						this->velocityVector.y = Globals::gravity * 0.02f;
						break;
					case CollideDirection::BOTTOM:
						if (this->jumpState == JumpState::FALLING && list_CollisionInfo.front()->collideObjCategory == Category::TERRAIN) {
							this->land();
						}
						this->blockState.bottom.isBlocking = true;
						this->blockState.bottom.blockCoordinate = list_CollisionInfo.front()->blockCoordinate;
						this->setLocation(x_location + list_CollisionInfo.front()->collideObjVelocityVector.x * prev_deltaTime, y_location);
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

void Player::die() {
	if (dying) return;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation_Dying.tga");

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 11, 1, 0, 0.2f);
	animation->SetSize(width, height);
	dying = true;
	this->velocityVector = Vector2(0.0f, 0.0f);
}
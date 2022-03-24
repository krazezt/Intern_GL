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

	movement_speed = 350;
	totalTime = 0;
	playing = false;

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 7, 1, 0, 0.2f);
	animation->SetSize(300, 200);

	texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation_IDLE_Left.tga");
	IDLE_Left_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 3, 1, 0, 0.5f);
	IDLE_Left_Animation->SetSize(300, 200);

	texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation_IDLE_Right.tga");
	IDLE_Right_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 3, 1, 0, 0.5f);
	IDLE_Right_Animation->SetSize(300, 200);

	texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation_MoveLeft.tga");
	moveLeft_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 1, 0, 0.075f);
	moveLeft_Animation->SetSize(300, 200);

	texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation_MoveRight.tga");
	moveRight_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 1, 0, 0.075f);
	moveRight_Animation->SetSize(300, 200);

	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, 150, 100);

	this->setLocation(240, 400);
}

void Player::update(float deltaTime) {
	totalTime += deltaTime;
	if (totalTime > 1.0f && playing == false) {
		this->animation = IDLE_Right_Animation;
		this->setLocation(x_location, y_location);
		playing = true;
	}

	switch (this->moveState) {
		case MoveState::MOVE_RIGHT:
			this->setLocation(x_location + velocityScale * movement_speed * deltaTime, y_location);
			break;
		case MoveState::MOVE_LEFT:
			this->setLocation(x_location - velocityScale * movement_speed * deltaTime, y_location);
			break;
		default:
			break;
	}

	this->animation->Update(deltaTime);
	this->collisionBox->update(deltaTime);
}

void Player::draw() {
	this->animation->Draw();
	this->collisionBox->draw();
}

void Player::stopMove() {
	if (this->moveState == MoveState::MOVE_RIGHT)
		this->animation = IDLE_Right_Animation;
	else this->animation = IDLE_Left_Animation;

	this->moveState = MoveState::IDLE;

	this->setLocation(x_location, y_location);
}

void Player::moveRight() {

}

void Player::horizontalMove(MoveState moveState, float velocityScale) {

	this->moveState = moveState;
	this->velocityScale = velocityScale;

	switch (moveState)
	{
		case MoveState::MOVE_RIGHT:
			this->animation = moveRight_Animation;
			break;
		case MoveState::MOVE_LEFT:
			this->animation = moveLeft_Animation;
			break;
		default:
			break;
	}
}

void Player::setCategory(Category category) {
	this->category = category;
}
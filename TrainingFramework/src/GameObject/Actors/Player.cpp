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

	int size_x = 150, size_y = 100;

	movement_speed = 350;
	totalTime = 0;
	playing = false;

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 7, 1, 0, 0.2f);
	animation->SetSize(size_x, size_y);

	texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation_IDLE_Right.tga");
	IDLE_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 3, 1, 0, 0.5f);
	IDLE_Animation->SetSize(size_x, size_y);

	texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation_MoveRight.tga");
	move_Animation = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 1, 0, 0.075f);
	move_Animation->SetSize(size_x, size_y);

	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, size_x, size_y);

	this->setLocation(240, 400);
	// this->animation->SetRotation(Vector3(PI, 0.0f, 0.0f));
}

void Player::update(float deltaTime) {
	totalTime += deltaTime;
	if (totalTime > 1.0f && playing == false) {
		this->animation = IDLE_Animation;
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
	this->animation = IDLE_Animation;
	if (this->moveState == MoveState::MOVE_RIGHT)
		this->animation->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
	else this->animation->SetRotation(Vector3(0.0f, PI, 0.0f));
	this->moveState = MoveState::IDLE;

	this->setLocation(x_location, y_location);
}

void Player::moveRight() {

}

void Player::horizontalMove(MoveState moveState, float velocityScale) {
	this->moveState = moveState;
	this->velocityScale = velocityScale;
	this->animation = move_Animation;

	switch (this->moveState)
	{
		case MoveState::MOVE_RIGHT:
			this->animation->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			break;
		case MoveState::MOVE_LEFT:
			this->animation->SetRotation(Vector3(0.0f, PI, 0.0f));
			break;
		default:
			break;
	}
}

void Player::setCategory(Category category) {
	this->category = category;
}
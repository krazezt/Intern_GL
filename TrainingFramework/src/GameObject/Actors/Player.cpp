#include "Player.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteAnimation.h"

void Player::init() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation1.tga");

	

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 1, 0, 0.1f);
	animation->SetSize(334, 223);

	this->setLocation(240, 400);

	movement_speed = 200;
}

void Player::update(float deltaTime) {
	switch (this->moveState)
	{
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
}

void Player::draw() {
	this->animation->Draw();
}

void Player::stopMove() {
	this->moveState = MoveState::IDLE;

	auto texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation1.tga");
	this->animation->SetTexture(texture);
}

void Player::moveRight() {

}

void Player::horizontalMove(MoveState moveState, int velocityScale) {
	this->moveState = moveState;
	this->velocityScale = velocityScale;

	switch (moveState)
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

	auto texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation2.tga");
	this->animation->SetTexture(texture);
}
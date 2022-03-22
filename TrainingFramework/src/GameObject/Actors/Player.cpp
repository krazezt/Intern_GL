#include "Player.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteAnimation.h"

void Player::init() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation1.tga");

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 1, 0, 0.1f);
	animation->Set2DPosition(240, 400);
	animation->SetSize(334, 223);
}

void Player::update(float deltaTime) {
	this->animation->Update(deltaTime);
}

void Player::draw() {
	this->animation->Draw();
}
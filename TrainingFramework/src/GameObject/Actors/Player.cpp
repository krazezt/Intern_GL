#include "Player.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteAnimation.h"

void Player::init() {}

void Player::setAnimation(std::shared_ptr<SpriteAnimation> animation) {
	Player::animation = animation;
}

void Player::setLocation(int location_X, int location_Y) {
	Player::x_location = location_X;
	Player::y_location = location_Y;
}

//void Player::show() {
//	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
//	auto texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation1.tga");
//	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
//
//	animation->Set2DPosition(Player::x_location, Player::y_location);
//	animation->SetSize(334, 223);
//	animation->Draw();
//}
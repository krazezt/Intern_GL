#include "Player1.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteAnimation.h"

void Player1::init() {}

void Player1::setAnimation(std::shared_ptr<SpriteAnimation> animation) {
	Player1::animation = animation;
}

void Player1::setLocation(int location_X, int location_Y) {
	Player1::x_location = location_X;
	Player1::y_location = location_Y;
}

void Player1::show() {
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Megaman_animation1.tga");
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");

	animation->Set2DPosition(Player1::x_location, Player1::y_location);
	animation->SetSize(334, 223);
	animation->Draw();
}
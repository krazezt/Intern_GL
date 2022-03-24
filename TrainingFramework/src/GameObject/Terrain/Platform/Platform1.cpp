#include "Platform1.h"
#include "ResourceManagers.h"

Platform1::Platform1() : StaticTerrain() {};
Platform1::~Platform1() {};

void Platform1::init(float x_location, float y_location) {
	this->x_location = x_location;
	this->y_location = y_location;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Terrain1.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	sprite2D = std::make_shared<Sprite2D>(model, shader, texture);
	sprite2D->Set2DPosition(this->x_location, this->y_location);
	sprite2D->SetSize(300, 300);

	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, 300, 300);
};
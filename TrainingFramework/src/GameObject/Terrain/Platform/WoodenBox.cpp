#include "WoodenBox.h"
#include "ResourceManagers.h"

WoodenBox::WoodenBox() : StaticTerrain() {
	this->category = Category::TERRAIN;
};
WoodenBox::~WoodenBox() {};

void WoodenBox::init(float x_location, float y_location) {
	this->x_location = x_location;
	this->y_location = y_location;

	float width = 100, height = 100;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("WoodenBox.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	sprite2D = std::make_shared<Sprite2D>(model, shader, texture);
	sprite2D->Set2DPosition(this->x_location, this->y_location);
	sprite2D->SetSize(width, height);

	this->initCollisionBox(this->x_location, this->y_location, width, height);
	this->velocityVector = Vector2(0.0f, 0.0f);
};

void WoodenBox::initCollisionBox(float x_location, float y_location, float width, float height) {
	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, width, height);
}

void WoodenBox::setLocation(float x_location, float y_location) {
	this->collisionBox->setLocation(x_location, y_location);
	this->sprite2D->Set2DPosition(x_location, y_location);
	this->x_location = x_location;
	this->y_location = y_location;
}
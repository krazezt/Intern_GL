#include "Platform2.h"
#include "ResourceManagers.h"

Platform2::Platform2() : BaseTerrain() {
	this->category = Category::TERRAIN;
};
Platform2::~Platform2() {};

void Platform2::init(float x_location, float y_location) {
	this->x_location = x_location;
	this->y_location = y_location;

	float width = 350, height = 80;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Platform.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	sprite2D = std::make_shared<Sprite2D>(model, shader, texture);
	sprite2D->Set2DPosition(this->x_location, this->y_location);
	sprite2D->SetSize(width, height);

	this->initCollisionBox(this->x_location, this->y_location, width, height);
	this->velocityVector = Vector2(150.0f, 0.0f);
};

void Platform2::initCollisionBox(float x_location, float y_location, float width, float height) {
	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, width, height);
}

void Platform2::setLocation(float x_location, float y_location) {
	this->collisionBox->setLocation(x_location, y_location);
	this->sprite2D->Set2DPosition(x_location, y_location);
	this->x_location = x_location;
	this->y_location = y_location;
}

void Platform2::update(float deltaTime) {
	if (x_location - this->collisionBox->getWidth() <= 0 || x_location + this->collisionBox->getWidth() >= Globals::screenWidth) {
		this->velocityVector.x *= -1;
	}

	this->setLocation(x_location + this->velocityVector.x * deltaTime, y_location + velocityVector.y * deltaTime);
	this->sprite2D->Update(deltaTime);
	this->collisionBox->update(deltaTime);
};
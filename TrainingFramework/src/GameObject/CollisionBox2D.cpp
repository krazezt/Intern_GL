#include "CollisionBox2D.h"
#include "ResourceManagers.h"

CollisionBox2D::CollisionBox2D() {}
CollisionBox2D::~CollisionBox2D() {}

void CollisionBox2D::init(float x_location, float y_location, float width, float height) {
	this->x_location = x_location;
	this->y_location = y_location;
	this->width = width;
	this->height = height;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Test_box.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	this->Test_box = std::make_shared<Sprite2D>(model, shader, texture);
	this->Test_box->Set2DPosition(this->x_location, this->y_location);
	this->Test_box->SetSize(this->width, this->height);

	this->showTestBox = true;
}

bool CollisionBox2D::detectCollision(CollisionBox2D box1, CollisionBox2D box2) {
	return true;
};

void CollisionBox2D::setLocation(float x_location, float y_location) {
	this->x_location = x_location;
	this->y_location = y_location;
	this->Test_box->Set2DPosition(x_location, y_location);
};

void CollisionBox2D::update(float deltaTime) {
	if (showTestBox)
		this->Test_box->Update(deltaTime);
}

void CollisionBox2D::draw() {
	if (showTestBox)
		this->Test_box->Draw();
}
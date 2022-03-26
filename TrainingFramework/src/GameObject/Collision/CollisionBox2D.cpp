#include "CollisionBox2D.h"
#include "ResourceManagers.h"
#include "GameConfig.h"

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

	this->showTestBox = SHOW_HITBOX;
}

bool CollisionBox2D::detectCollision(std::shared_ptr<CollisionBox2D> box) {
	float x1, x2, y1, y2;
	
	// Calculate the coordinates of the top-left vertex
	x1 = this->x_location - this->width/2;
	x2 = box->getLocationX() - box->getWidth()/2;
	y1 = this->y_location - this->height/2;
	y2 = box->getLocationY() - box->getHeight()/2;

	if (
		((x1 + this->width) >= x2) &&
		((x2 + box->getWidth()) >= x1) &&
		((y1 + this->height) >= y2) &&
		((y2 + box->getHeight()) >= y1)
		) return true;
	else return false;
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
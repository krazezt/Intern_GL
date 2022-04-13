#include "MapEdge.h"
#include "ResourceManagers.h"

MapEdge::MapEdge() : StaticTerrain() {
	this->category = Category::TERRAIN;
};
MapEdge::~MapEdge() {};

void MapEdge::init(float x_location, float y_location) {
	this->x_location = x_location;
	this->y_location = y_location;

	float width = Globals::screenWidth + 300, height = Globals::screenHeight + 300;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("MapEdge.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	sprite2D = std::make_shared<Sprite2D>(model, shader, texture);
	sprite2D->Set2DPosition(this->x_location, this->y_location);
	sprite2D->SetSize(width, height);

	this->initCollisionBox(this->x_location, this->y_location, width, height);
	this->velocityVector = Vector2(0.0f, 0.0f);
};

void MapEdge::init(EdgeSide side) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("MapEdge.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	int width = 300, height = 300;

	switch (side)
	{
	case EdgeSide::TOP:
		x_location = Globals::screenWidth / 2;
		y_location = -1 * Globals::screenWidth / 12;
		width = Globals::screenWidth + Globals::screenWidth / 6;
		height = Globals::screenWidth / 6;
		break;
	case EdgeSide::LEFT:
		x_location = -1 * Globals::screenWidth / 12;
		y_location = Globals::screenHeight / 2;
		width = Globals::screenWidth / 6;
		height = Globals::screenHeight + Globals::screenWidth / 6;
		break;
	case EdgeSide::BOTTOM:
		x_location = Globals::screenWidth / 2;
		y_location = Globals::screenHeight + Globals::screenWidth / 12;
		width = Globals::screenWidth + Globals::screenWidth / 6;
		height = Globals::screenWidth / 6;
		break;
	case EdgeSide::RIGHT:
		x_location = Globals::screenWidth + Globals::screenWidth / 12;
		y_location = Globals::screenHeight / 2;
		width = Globals::screenWidth / 6;
		height = Globals::screenHeight + Globals::screenWidth / 6;
		break;
	default:
		break;
	}

	width += Globals::screenWidth / 180;
	height += Globals::screenWidth / 180;

	sprite2D = std::make_shared<Sprite2D>(model, shader, texture);
	sprite2D->Set2DPosition(this->x_location, this->y_location);
	sprite2D->SetSize(width, height);

	this->initCollisionBox(this->x_location, this->y_location, width, height);
	this->velocityVector = Vector2(0.0f, 0.0f);
};

void MapEdge::initCollisionBox(float x_location, float y_location, float width, float height) {
	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, width, height);
}

void MapEdge::setLocation(float x_location, float y_location) {
	this->collisionBox->setLocation(x_location, y_location);
	this->sprite2D->Set2DPosition(x_location, y_location);
	this->x_location = x_location;
	this->y_location = y_location;
}
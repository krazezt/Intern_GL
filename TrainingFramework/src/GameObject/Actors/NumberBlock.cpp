#include "NumberBlock.h"
#include "Shader.h"
#include "Texture.h"

NumberBlock::NumberBlock() {
	category = Category::NUMBER_BLOCK;
}
NumberBlock::~NumberBlock() {}

void NumberBlock::init(float x_location, float y_location) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("NumberBlock.tga");

	width = Globals::screenWidth / 18;
	height = Globals::screenWidth / 18;
	movement_speed = 0;
	prev_deltaTime = 0;
	value = 0;
	isTriggering = false;

	texture_normal = ResourceManagers::GetInstance()->GetTexture("NumberBlock.tga");
	texture_triggering = ResourceManagers::GetInstance()->GetTexture("NumberBlock_triggering.tga");

	animation = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 1, 0, 1.0f);
	animation->SetSize(width, height);

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	textValue = std::make_shared<Text>(shader, font, "1", TextColor::RED, Globals::screenWidth / 600);
	textValue->Set2DPosition(Vector2(x_location - Globals::screenWidth / 120, y_location + Globals::screenWidth / 60));

	this->initCollisionBox(x_location, y_location, width, height);
	this->velocityVector = Vector2(0.0f, 0.0f);
	this->blockState.reset();

	this->setLocation(x_location, y_location);
}

void NumberBlock::initCollisionBox(float x_location, float y_location, float width, float height) {
	collisionBox = std::make_shared<CollisionBox2D>();
	collisionBox->init(this->x_location, this->y_location, width, height);
}

void NumberBlock::update(float deltaTime) {
	this->consumeCollision();

	this->setLocation(x_location + velocityVector.x * deltaTime, y_location + velocityVector.y * deltaTime);

	this->animation->Update(deltaTime);
	this->collisionBox->update(deltaTime);
	this->prev_deltaTime = deltaTime;
}

void NumberBlock::draw() {
	this->animation->Draw();
	this->collisionBox->draw();
	this->textValue->Draw();
}

void NumberBlock::consumeCollision() {
	if (list_CollisionInfo.empty() && isTriggering) {
		ResourceManagers::GetInstance()->PlaySFX("134 - PiPiPi.wav");
		isTriggering = false;
		animation->SetTexture(texture_normal);
	}

	while (!list_CollisionInfo.empty()) {
		switch (list_CollisionInfo.front()->collisionType) {
		case Collision::IGNORED:
			break;
		case Collision::BLOCK:
			break;
		case Collision::OVERLAP:
			if (!isTriggering) {
				ResourceManagers::GetInstance()->PlaySFX("24 - EnergyFill.wav");
				switch (list_CollisionInfo.front()->collideObjCategory) {
					case Category::PLAYER:
						isTriggering = true;
						animation->SetTexture(texture_triggering);
						break;
					default:
						break;
				}
			}
			break;
		default:
			break;
		}

		list_CollisionInfo.pop_front();
	}
}

void NumberBlock::setValue(int newValue) {
	this->value = newValue;

	char str[3];
	sprintf(str, "%d", this->value);
	textValue->SetText(str);
	textValue->Set2DPosition(Vector2(value < 10 ? (x_location - Globals::screenWidth / 120) : (x_location - Globals::screenWidth / 51.4f), y_location + Globals::screenWidth / 60.0f));
}
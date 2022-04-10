#include "GSPlayTrigger.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"

#include "Terrain/Platform/MapEdge.h"
#include "Terrain/Platform/WoodenBox.h"

GSPlayTrigger::GSPlayTrigger()
{
}


GSPlayTrigger::~GSPlayTrigger()
{
}


void GSPlayTrigger::Init()
{
	m_Test = 1;
	pausing = false;
	isEnd = false;
	initScore = 100;
	totalTime = 0.0f;
	win = false;
	Globals::gravity = 0.0f;

	score = initScore;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Background2.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	m_pauseButton = std::make_shared<GameButton>(model, shader, texture);
	m_pauseButton->Set2DPosition(Globals::screenWidth - 150, 50);
	m_pauseButton->SetSize(50, 50);
	m_pauseButton->SetOnClick([this]() {
		Pause();
		});
	m_listButton.push_back(m_pauseButton);

	// Map edges
	std::shared_ptr<MapEdge> mapEdge;

	mapEdge = std::make_shared<MapEdge>();
	mapEdge->init(EdgeSide::TOP);
	m_listTerrain.push_back(mapEdge);

	mapEdge = std::make_shared<MapEdge>();
	mapEdge->init(EdgeSide::LEFT);
	m_listTerrain.push_back(mapEdge);

	mapEdge = std::make_shared<MapEdge>();
	mapEdge->init(EdgeSide::BOTTOM);
	m_listTerrain.push_back(mapEdge);

	mapEdge = std::make_shared<MapEdge>();
	mapEdge->init(EdgeSide::RIGHT);
	m_listTerrain.push_back(mapEdge);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared<Text>(shader, font, "score: 10", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	CollisionManager::GetInstance()->init();

	// Player
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->init(1020, 650);
	player->bindKeys(KEY_MOVE_LEFT, KEY_MOVE_RIGHT, -1, KEY_MOVE_FORWARD, KEY_MOVE_BACKWARD);
	m_listPlayer.push_back(player);

	if (Globals::playerCount > 1) {
		player = std::make_shared<Player>();
		player->init(1200, 650);
		player->bindKeys(KEY_LEFT, KEY_RIGHT, -1, KEY_UP, KEY_DOWN);
		m_listPlayer.push_back(player);
	}

	// Level
	std::shared_ptr<BaseTerrain> terrain;

	terrain = std::make_shared<WoodenBox>();
	terrain->init(200, 200);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<WoodenBox>();
	terrain->init(700, 200);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<WoodenBox>();
	terrain->init(1500, 200);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<WoodenBox>();
	terrain->init(1000, 420);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<WoodenBox>();
	terrain->init(450, 600);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<WoodenBox>();
	terrain->init(1300, 600);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<WoodenBox>();
	terrain->init(1000, 750);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<WoodenBox>();
	terrain->init(1700, 750);
	m_listTerrain.push_back(terrain);

	// Trigger block
	m_triggerBlock = std::make_shared<TriggerBlock>();
	m_triggerBlock->init(850, 650);

	// Triggerer
	std::shared_ptr<Triggerer> triggerer;

	triggerer = std::make_shared<Triggerer>();
	triggerer->init(450, 200);
	m_listTriggerer.push_back(triggerer);

	triggerer = std::make_shared<Triggerer>();
	triggerer->init(1000, 200);
	m_listTriggerer.push_back(triggerer);

	triggerer = std::make_shared<Triggerer>();
	triggerer->init(1700, 200);
	m_listTriggerer.push_back(triggerer);

	triggerer = std::make_shared<Triggerer>();
	triggerer->init(450, 420);
	m_listTriggerer.push_back(triggerer);

	triggerer = std::make_shared<Triggerer>();
	triggerer->init(700, 420);
	m_listTriggerer.push_back(triggerer);

	triggerer = std::make_shared<Triggerer>();
	triggerer->init(1500, 420);
	m_listTriggerer.push_back(triggerer);

	triggerer = std::make_shared<Triggerer>();
	triggerer->init(1300, 750);
	m_listTriggerer.push_back(triggerer);

	triggerer = std::make_shared<Triggerer>();
	triggerer->init(700, 750);
	m_listTriggerer.push_back(triggerer);
}

void GSPlayTrigger::Exit()
{
}


void GSPlayTrigger::Pause() {
	pausing = true;
	auto texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	m_pauseButton->SetTexture(texture);

	m_pauseButton->SetOnClick([this]() {
			Resume();
		});
}

void GSPlayTrigger::Resume() {
	pausing = false;
	auto texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	m_pauseButton->SetTexture(texture);

	m_pauseButton->SetOnClick([this]() {
			Pause();
		});
}


void GSPlayTrigger::HandleEvents()
{
}

void GSPlayTrigger::HandleKeyEvents(int key, bool bIsPressed)
{
	if (this->isEnd || pausing) return;
	for (auto i : m_listPlayer) {
		i->handleKeyEvent(key, bIsPressed);
	}
}

void GSPlayTrigger::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlayTrigger::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlayTrigger::checkEnd() {
	if (score <= 0) {
		win = false;
		isEnd = true;
		initEndgameText();
		return;
	}
	
	for (auto i : m_listTriggerer) {
		if (!i->checkTriggered()) return;
	}

	win = true;
	isEnd = true;
	initEndgameText();
}

void GSPlayTrigger::initEndgameText() {
	char str[30];
	if (win) {
		sprintf(str, "You won! (%d pts)", this->score);
	}
	else {
		sprintf(str, "You lose!");
	}

	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_endGame = std::make_shared<Text>(shader, font, str, TextColor::RED, 2.0);
	m_endGame->Set2DPosition(Vector2(Globals::screenWidth / 2 - 200, Globals::screenHeight / 2));
}

void GSPlayTrigger::Update(float deltaTime)
{
	this->checkEnd();
	if (this->isEnd) return;

	totalTime += deltaTime;

	if (!pausing) {
		if (score != std::round(totalTime)) {
			score = initScore - std::round(totalTime);
			char str[30];
			sprintf(str, "Time left: %d seconds", score);

			m_score->SetText(str);
		}

		m_triggerBlock->update(deltaTime);

		for (auto it : m_listPlayer) {
			it->update(deltaTime);
			if (m_triggerBlock->getCollisionBox()->detectCollision(it->getCollisionBox())) {
				m_triggerBlock->applyCollision(it);
			}
		}

		for (auto it : m_listButton) {
			it->Update(deltaTime);
		}

		for (auto it : m_listActor) {
			it->update(deltaTime);
		}

		for (auto it : m_listTerrain) {
			for (auto i : m_listPlayer)
				if (i->getCollisionBox()->detectCollision(it->getCollisionBox())) {
					i->applyCollision(it);
				}

			if (m_triggerBlock->getCollisionBox()->detectCollision(it->getCollisionBox())) {
				m_triggerBlock->applyCollision(it);
			}

			it->update(deltaTime);
		}

		for (auto it : m_listTriggerer) {
			if (m_triggerBlock->getCollisionBox()->detectCollision(it->getCollisionBox())) {
				m_triggerBlock->applyCollision(it);
				it->trigger();
			}

			for (auto i : m_listPlayer)
				if (i->getCollisionBox()->detectCollision(it->getCollisionBox())) {
					i->applyCollision(it);
				}
		}
	}
}

void GSPlayTrigger::Draw()
{
	m_background->Draw();

	for (auto it : m_listPlayer) {
		it->draw();
	}

	for (auto it : m_listActor) {
		it->draw();
	}

	for (auto it : m_listTerrain) {
		it->draw();
	}

	for (auto it : m_listTriggerer) {
		it->draw();
	}

	m_triggerBlock->draw();

	m_score->Draw();
	if (this->isEnd) m_endGame->Draw();

	for (auto it : m_listButton) {
		it->Draw();
	}
}
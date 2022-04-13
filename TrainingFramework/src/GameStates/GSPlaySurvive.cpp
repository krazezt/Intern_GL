#include "GSPlaySurvive.h"

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

#include "Actors/Enemy/Enemy1.h"
#include "Actors/Enemy/Enemy2.h"
#include "Terrain/Platform/MapEdge.h"
#include "Terrain/Platform/Platform1.h"
#include "Terrain/Platform/Platform2.h"

std::list<std::shared_ptr<Actor>>	GSPlaySurvive::m_listSpwActor;

GSPlaySurvive::GSPlaySurvive()
{
}


GSPlaySurvive::~GSPlaySurvive()
{
}


void GSPlaySurvive::Init()
{
	m_Test = 1;
	pausing = false;
	isLose = false;
	score = 0;
	totalTime = 0.0f;
	Globals::gravity = Globals::screenWidth / 0.36f;

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
	button->Set2DPosition(Globals::screenWidth - Globals::screenWidth / 36, Globals::screenWidth / 36);
	button->SetSize(Globals::screenWidth / 36, Globals::screenWidth / 36);
	button->SetOnClick([this]() {
			GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	m_pauseButton = std::make_shared<GameButton>(model, shader, texture);
	m_pauseButton->Set2DPosition(Globals::screenWidth - Globals::screenWidth / 12, Globals::screenWidth / 36);
	m_pauseButton->SetSize(Globals::screenWidth / 36, Globals::screenWidth / 36);
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
	m_score = std::make_shared<Text>(shader, font, "Score: 0", TextColor::RED, Globals::screenWidth / 1800);
	m_score->Set2DPosition(Vector2(Globals::screenWidth / 360, Globals::screenWidth / 53));

	// Player
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->init(Globals::screenWidth / 1.8f, Globals::screenWidth / 2.8f);
	player->bindKeys(KEY_MOVE_LEFT, KEY_MOVE_RIGHT, KEY_JUMP, -1, -1);
	m_listPlayer.push_back(player);

	if (Globals::playerCount > 1) {
		player = std::make_shared<Player>();
		player->init(Globals::screenWidth / 1.7f, Globals::screenWidth / 2.8f);
		player->bindKeys(KEY_LEFT, KEY_RIGHT, KEY_UP, -1, -1);
		m_listPlayer.push_back(player);
	}

	// Level
	std::shared_ptr<BaseTerrain> terrain;

	terrain = std::make_shared<Platform1>();
	terrain->init(Globals::screenWidth / 2.6f, Globals::screenWidth / 2.25f);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<Platform1>();
	terrain->init(Globals::screenWidth / 1.6364f, Globals::screenWidth / 2.25f);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<Platform1>();
	terrain->init(Globals::screenWidth / 4.5f, Globals::screenWidth / 4.5f);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<Platform1>();
	terrain->init(Globals::screenWidth / 1.3f, Globals::screenWidth / 4.5f);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<Platform2>();
	terrain->init(Globals::screenWidth / 2, Globals::screenWidth / 3);
	m_listTerrain.push_back(terrain);

	// Enemies
	std::shared_ptr<Enemy> enemy;

	enemy = std::make_shared<Enemy1>();
	enemy->init(Globals::screenWidth / 1.125f, Globals::screenWidth / 25.7f);
	m_listActor.push_back(enemy);

	enemy = std::make_shared<Enemy1>();
	enemy->init(Globals::screenWidth / 4.5f, Globals::screenWidth / 25.7f);
	m_listActor.push_back(enemy);

	enemy = std::make_shared<Enemy2>();
	enemy->init(Globals::screenWidth / 1.8f, Globals::screenWidth / 6);
	m_listActor.push_back(enemy);

	enemy = std::make_shared<Enemy2>();
	enemy->init(Globals::screenWidth / 9, Globals::screenWidth / 6);
	m_listActor.push_back(enemy);

	enemy = std::make_shared<Enemy2>();
	enemy->init(Globals::screenWidth / 3, Globals::screenWidth / 2.6f);
	m_listActor.push_back(enemy);

	enemy = std::make_shared<Enemy2>();
	enemy->init(Globals::screenWidth / 1.3f, Globals::screenWidth / 2.6f);
	m_listActor.push_back(enemy);
}

void GSPlaySurvive::Exit()
{
	m_listSpwActor.clear();
}


void GSPlaySurvive::Pause() {
	pausing = true;
	auto texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	m_pauseButton->SetTexture(texture);

	m_pauseButton->SetOnClick([this]() {
		Resume();
	});
}

void GSPlaySurvive::Resume() {
	pausing = false;
	auto texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	m_pauseButton->SetTexture(texture);

	m_pauseButton->SetOnClick([this]() {
		Pause();
	});
}


void GSPlaySurvive::HandleEvents()
{
}

void GSPlaySurvive::HandleKeyEvents(int key, bool bIsPressed)
{
	if (pausing) return;
	for (auto i : m_listPlayer) {
		i->handleKeyEvent(key, bIsPressed);
	}
}

void GSPlaySurvive::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlaySurvive::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlaySurvive::checkLose() {
	bool lose = true;
	for (auto it : m_listPlayer) {
		if (!it->isDied()) lose = false;
	}

	char str[30];
	sprintf(str, "End game (%d pts)", this->score);

	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_endGame = std::make_shared<Text>(shader, font, str, TextColor::RED, Globals::screenWidth / 900);
	m_endGame->Set2DPosition(Vector2(Globals::screenWidth / 2 - Globals::screenWidth / 9, Globals::screenHeight / 2));
	this->isLose = lose;
}

void GSPlaySurvive::Update(float deltaTime)
{
	if (this->isLose) return;

	this->checkLose();

	totalTime += deltaTime;

	if (!pausing) {
		if (score != std::round(totalTime)) {
			score = std::round(totalTime);
			char str[30];
			sprintf(str, "Score: %d", score);

			m_score->SetText(str);
		}

		for (auto it : m_listPlayer) {
			it->update(deltaTime);
		}

		for (auto it : m_listButton) {
			it->Update(deltaTime);
		}

		for (auto it : m_listActor) {
			for (auto i : m_listPlayer)
				if (i->getCollisionBox()->detectCollision(it->getCollisionBox())) {
					i->applyCollision(it);
				}
			it->update(deltaTime);
		}

		for (auto it : m_listTerrain) {
			for (auto i : m_listPlayer)
				if (i->getCollisionBox()->detectCollision(it->getCollisionBox())) {
					i->applyCollision(it);
				}
			it->update(deltaTime);
		}

		for (auto it : m_listSpwActor) {
			for (auto i : m_listPlayer)
				if (i->getCollisionBox()->detectCollision(it->getCollisionBox())) {
					i->applyCollision(it);
				}
			it->update(deltaTime);
		}
	}
}

void GSPlaySurvive::Draw()
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

	for (auto it : m_listSpwActor) {
		it->draw();
	}

	m_score->Draw();
	if (this->isLose) m_endGame->Draw();

	for (auto it : m_listButton) {
		it->Draw();
	}
}

void GSPlaySurvive::addSpawnedActor(std::shared_ptr<Actor> spawnedActor) {
	m_listSpwActor.push_back(spawnedActor);
}

void GSPlaySurvive::removeSpawnedActor(std::shared_ptr<Actor> spawnedActor) {
	m_listSpwActor.remove(spawnedActor);
}
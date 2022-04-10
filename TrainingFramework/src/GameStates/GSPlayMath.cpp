#include <cstdlib>
#include <ctime>

#include "GSPlayMath.h"

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

GSPlayMath::GSPlayMath()
{
}


GSPlayMath::~GSPlayMath()
{
}


void GSPlayMath::Init()
{
	pausing = false;
	isEnd = false;
	score = 0;
	timeLeft = 100;
	totalTime = 0.0f;
	Globals::gravity = 5000.0f;

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
	player->bindKeys(KEY_MOVE_LEFT, KEY_MOVE_RIGHT, KEY_JUMP, -1, -1);
	m_listPlayer.push_back(player);

	if (Globals::playerCount > 1) {
		player = std::make_shared<Player>();
		player->init(1100, 650);
		player->bindKeys(KEY_LEFT, KEY_RIGHT, KEY_UP, -1, -1);
		m_listPlayer.push_back(player);
	}

	// Level
	std::shared_ptr<BaseTerrain> terrain;

	terrain = std::make_shared<Platform1>();
	terrain->init(700, 800);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<Platform1>();
	terrain->init(1100, 800);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<Platform1>();
	terrain->init(400, 400);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<Platform1>();
	terrain->init(1400, 400);
	m_listTerrain.push_back(terrain);

	terrain = std::make_shared<Platform2>();
	terrain->init(900, 600);
	m_listTerrain.push_back(terrain);
}

void GSPlayMath::Exit() {
}


void GSPlayMath::Pause() {
	pausing = true;
	auto texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	m_pauseButton->SetTexture(texture);

	m_pauseButton->SetOnClick([this]() {
			Resume();
		});
}

void GSPlayMath::Resume() {
	pausing = false;
	auto texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	m_pauseButton->SetTexture(texture);

	m_pauseButton->SetOnClick([this]() {
			Pause();
		});
}


void GSPlayMath::HandleEvents()
{
}

void GSPlayMath::HandleKeyEvents(int key, bool bIsPressed)
{
	if (pausing) return;
	for (auto i : m_listPlayer) {
		i->handleKeyEvent(key, bIsPressed);
	}
}

void GSPlayMath::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlayMath::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlayMath::checkEndgame() {
	
}

void GSPlayMath::Update(float deltaTime)
{
	if (this->isEnd) return;

	this->checkEndgame();

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
			it->update(deltaTime);
		}

		for (auto it : m_listTerrain) {
			for (auto i : m_listPlayer)
				if (i->getCollisionBox()->detectCollision(it->getCollisionBox())) {
					i->applyCollision(it);
				}
			it->update(deltaTime);
		}
	}
}

void GSPlayMath::Draw()
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

	m_score->Draw();
	if (this->isEnd) m_endGame->Draw();

	for (auto it : m_listButton) {
		it->Draw();
	}
}

void GSPlayMath::initRandomSeed() {
	srand(time(NULL));
};

int	 GSPlayMath::getRandomValue(int from, int to) {
	return (rand() % (from - to + 1) + from);
};

void GSPlayMath::setupNewRound() {};
bool GSPlayMath::checkEndRound() {};
bool GSPlayMath::checkEndGame() {};
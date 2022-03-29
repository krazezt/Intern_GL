#include "GSPlay.h"

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

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	m_Test = 1;
	pausing = false;
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

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared<Text>(shader, font, "score: 10", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	CollisionManager::GetInstance()->init();

	// Player
	player = std::make_shared<Player>();
	player->init();

	m_listActor.push_back(player);

	// Level
	std::shared_ptr<BaseTerrain> terrain;
	terrain = std::make_shared<Platform1>();
	terrain->init(1600, 600);
	m_listTerrain.push_back(terrain);
}

void GSPlay::Exit()
{
	printf("%d", m_Test);
}


void GSPlay::Pause() {
	pausing = true;
	auto texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	m_pauseButton->SetTexture(texture);

	m_pauseButton->SetOnClick([this]() {
		Resume();
	});
}

void GSPlay::Resume() {
	pausing = false;
	auto texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	m_pauseButton->SetTexture(texture);

	m_pauseButton->SetOnClick([this]() {
		Pause();
	});
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (pausing) return;
	switch (key)
	{
	case KEY_MOVE_RIGHT:
		bIsPressed ? player->horizontalMove(MoveState::MOVE_RIGHT, 1.0f) : player->stopMove();
		break;
	case KEY_MOVE_LEFT:
		bIsPressed ? player->horizontalMove(MoveState::MOVE_LEFT, 1.0f) : player->stopMove();
		break;
	default:
		break;
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	if (!pausing) {
		for (auto it : m_listButton) {
			it->Update(deltaTime);
		}
		for (auto it : m_listAnimation) {
			it->Update(deltaTime);
		}
		for (auto it : m_listActor) {
			it->update(deltaTime);
		}
		for (auto it : m_listTerrain) {
			if (player->getCollisionBox()->detectCollision(it->getCollisionBox())) {
				player->applyCollision(it);
			}
			it->update(deltaTime);
		}
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
	for (auto it : m_listActor) {
		it->draw();
	}
	for (auto it : m_listTerrain) {
		it->draw();
	}
}
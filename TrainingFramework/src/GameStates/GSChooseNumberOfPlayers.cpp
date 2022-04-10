#include "GSChooseNumberOfPlayers.h"
#include "Camera.h"

int GSChooseNumberOfPlayers::n_o_player = 1;

GSChooseNumberOfPlayers::GSChooseNumberOfPlayers() : GameStateBase(StateType::STATE_CHOOSING_N_O_PLAYERS),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}

GSChooseNumberOfPlayers::~GSChooseNumberOfPlayers()
{
}


void GSChooseNumberOfPlayers::Init()
{
	switch (GameStateMachine::GetInstance()->getChoosingMode()) {
	case PlayMode::SURVIVE:
		minPlayer = 1;
		maxPlayer = 2;
		break;
	case PlayMode::TRIGGER:
		minPlayer = 1;
		maxPlayer = 2;
		break;
	case PlayMode::MATH:
		minPlayer = 2;
		maxPlayer = 2;
		break;
	default:
		break;
	}

	n_o_player = minPlayer;

	char str[10];

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Background3.tga");

	// State title
	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_textGameName = std::make_shared<Text>(shader, font, "Choose number of players", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	m_textGameName->Set2DPosition(Vector2(60, 200));

	// Player count
	sprintf(str, "%d players", n_o_player);
	m_textPlayerCount = std::make_shared<Text>(shader, font, str, Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	m_textPlayerCount->Set2DPosition(Vector2(Globals::screenWidth / 2 - 160, Globals::screenHeight / 2 + 20));

	// background
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
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

	// more player button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_next.tga");
	m_moreButton = std::make_shared<GameButton>(model, shader, texture);
	m_moreButton->Set2DPosition(Globals::screenWidth / 2 + 600, Globals::screenHeight / 2);
	m_moreButton->SetSize(200, 200);
	m_moreButton->SetOnClick([this]() {
			if (this->n_o_player + 1 > this->maxPlayer) {
				return;
			}
			this->n_o_player += 1;
			char str[10];
			sprintf(str, "%d players", n_o_player);
			m_textPlayerCount->SetText(str);
		});
	m_listButton.push_back(m_moreButton);

	// less player button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	m_lessButton = std::make_shared<GameButton>(model, shader, texture);
	m_lessButton->Set2DPosition(Globals::screenWidth / 2 - 600, Globals::screenHeight / 2);
	m_lessButton->SetSize(200, 200);
	m_lessButton->SetOnClick([this]() {
			if (this->n_o_player - 1 < this->minPlayer) {
				return;
			}
			this->n_o_player -= 1;
			char str[15];
			sprintf(str, "%d players", n_o_player);
			m_textPlayerCount->SetText(str);
		});
	m_listButton.push_back(m_lessButton);

	// Play button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_play.tga");
	m_playButton = std::make_shared<GameButton>(model, shader, texture);
	m_playButton->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 + 250);
	m_playButton->SetSize(200, 200);
	m_playButton->SetOnClick([this]() {
			Globals::playerCount = this->n_o_player;
			GameStateMachine::GetInstance()->ChangeState( GameStateMachine::GetInstance()->getGameStateByMode( GameStateMachine::GetInstance()->getChoosingMode() ) );
		});
	m_listButton.push_back(m_playButton);
}

void GSChooseNumberOfPlayers::Exit()
{
}

void GSChooseNumberOfPlayers::Pause()
{
}

void GSChooseNumberOfPlayers::Resume()
{
}


void GSChooseNumberOfPlayers::HandleEvents()
{
}

void GSChooseNumberOfPlayers::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSChooseNumberOfPlayers::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSChooseNumberOfPlayers::HandleMouseMoveEvents(int x, int y)
{
}

void GSChooseNumberOfPlayers::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSChooseNumberOfPlayers::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
	m_textPlayerCount->Draw();
}

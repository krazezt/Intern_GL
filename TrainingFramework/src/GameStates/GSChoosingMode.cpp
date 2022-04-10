#include "GSChoosingMode.h"
#include "Camera.h"

PlayMode GSChoosingMode::modeList[10] = {
	PlayMode::SURVIVE,
	PlayMode::TRIGGER,
};

GSChoosingMode::GSChoosingMode() : GameStateBase(StateType::STATE_CHOOSING_MODE),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}

GSChoosingMode::~GSChoosingMode()
{
}


void GSChoosingMode::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Background3.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
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

	// Next button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_next.tga");
	m_nextButton = std::make_shared<GameButton>(model, shader, texture);
	m_nextButton->Set2DPosition(Globals::screenWidth / 2 + 600, Globals::screenHeight / 2);
	m_nextButton->SetSize(200, 200);
	m_nextButton->SetOnClick([this]() {
			int i = this->getChoosingModeIndex();
			if (GSChoosingMode::modeList[i+1] == PlayMode::INVALID) return;

			this->setChoosingModeIndex(i + 1);
		});
	m_listButton.push_back(m_nextButton);

	// Prev button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	m_prevButton = std::make_shared<GameButton>(model, shader, texture);
	m_prevButton->Set2DPosition(Globals::screenWidth / 2 - 600, Globals::screenHeight / 2);
	m_prevButton->SetSize(200, 200);
	m_prevButton->SetOnClick([this]() {
			int i = this->getChoosingModeIndex();
			if (i == 0) return;

			this->setChoosingModeIndex(i - 1);
		});
	m_listButton.push_back(m_prevButton);

	// Confirm button
	texture = ResourceManagers::GetInstance()->GetTexture("abc.tga");
	m_modeButton = std::make_shared<GameButton>(model, shader, texture);
	m_modeButton->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_modeButton->SetSize(1000, 500);
	m_modeButton->SetOnClick([this]() {
			GameStateMachine::GetInstance()->setChoosingMode(modeList[this->getChoosingModeIndex()]);
			GameStateMachine::GetInstance()->ChangeState(StateType::STATE_CHOOSING_N_O_PLAYERS);
		});
	m_listButton.push_back(m_modeButton);

	// State title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_textGameName = std::make_shared< Text>(shader, font, "Choose Play Mode", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	m_textGameName->Set2DPosition(Vector2(60, 100));

	setChoosingModeIndex(0);
}

void GSChoosingMode::Exit()
{
}

void GSChoosingMode::Pause()
{
}

void GSChoosingMode::Resume()
{
}


void GSChoosingMode::HandleEvents()
{
}

void GSChoosingMode::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSChoosingMode::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSChoosingMode::HandleMouseMoveEvents(int x, int y)
{
}

void GSChoosingMode::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSChoosingMode::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
}

void GSChoosingMode::setChoosingModeIndex(int newModeIndex) {
	if (modeList[newModeIndex] == PlayMode::INVALID) return;
	std::shared_ptr<Texture> texture;

	switch (modeList[newModeIndex]) {
	case PlayMode::SURVIVE:
		texture = ResourceManagers::GetInstance()->GetTexture("Mode_Survive.tga");
		m_modeButton->SetTexture(texture);
		break;
	case PlayMode::TRIGGER:
		texture = ResourceManagers::GetInstance()->GetTexture("Background2.tga");
		m_modeButton->SetTexture(texture);
		break;
	default:
		break;
	}

	GameStateMachine::GetInstance()->setChoosingMode(modeList[newModeIndex]);
	this->choosingModeIndex = newModeIndex;
};

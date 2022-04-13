#include "GSTutorial.h"
#include "Camera.h"

GSTutorial::GSTutorial() : GameStateBase(StateType::STATE_CHOOSING_MODE),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}

GSTutorial::~GSTutorial()
{
}


void GSTutorial::Init()
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
	button->Set2DPosition(Globals::screenWidth - Globals::screenWidth / 36, Globals::screenWidth / 36);
	button->SetSize(Globals::screenWidth / 36, Globals::screenWidth / 36);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// Next button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_next.tga");
	m_nextButton = std::make_shared<GameButton>(model, shader, texture);
	m_nextButton->Set2DPosition(Globals::screenWidth / 2 + Globals::screenWidth / 3, Globals::screenHeight / 2);
	m_nextButton->SetSize(Globals::screenWidth / 9, Globals::screenWidth / 9);
	m_nextButton->SetOnClick([this]() {
		int i = this->getChoosingModeIndex();
		if (GSChoosingMode::modeList[i + 1] == PlayMode::INVALID) return;

		this->setChoosingModeIndex(i + 1);
		});
	m_listButton.push_back(m_nextButton);

	// Prev button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	m_prevButton = std::make_shared<GameButton>(model, shader, texture);
	m_prevButton->Set2DPosition(Globals::screenWidth / 2 - Globals::screenWidth / 3, Globals::screenHeight / 2);
	m_prevButton->SetSize(Globals::screenWidth / 9, Globals::screenWidth / 9);
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
	m_modeButton->SetSize(Globals::screenWidth / 1.8f, Globals::screenWidth / 3.6f);
	m_modeButton->SetOnClick([this]() {
		});
	m_listButton.push_back(m_modeButton);

	// State title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_textGameName = std::make_shared<Text>(shader, font, "Tutorial", Vector4(1.0f, 0.5f, 0.0f, 1.0f), Globals::screenWidth / 900);
	m_textGameName->Set2DPosition(Vector2(Globals::screenWidth / 30, Globals::screenWidth / 18));

	// Text tutorial
	m_textTutorial = std::make_shared<Text>(shader, font, "", Vector4(1.0f, 0.5f, 0.0f, 1.0f), Globals::screenWidth / 1800);
	m_textTutorial->Set2DPosition(Vector2(Globals::screenWidth / 4.5f, Globals::screenWidth / 12));

	setChoosingModeIndex(0);
}

void GSTutorial::Exit()
{
}

void GSTutorial::Pause()
{
}

void GSTutorial::Resume()
{
}


void GSTutorial::HandleEvents()
{
}

void GSTutorial::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSTutorial::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSTutorial::HandleMouseMoveEvents(int x, int y)
{
}

void GSTutorial::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSTutorial::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
	m_textTutorial->Draw();
}

void GSTutorial::setChoosingModeIndex(int newModeIndex) {
	if (GSChoosingMode::modeList[newModeIndex] == PlayMode::INVALID) return;
	std::shared_ptr<Texture> texture;

	switch (GSChoosingMode::modeList[newModeIndex]) {
	case PlayMode::SURVIVE:
		texture = ResourceManagers::GetInstance()->GetTexture("SurviveMode.tga");
		m_modeButton->SetTexture(texture);
		m_textTutorial->SetText("Runnn !!!");
		break;
	case PlayMode::TRIGGER:
		texture = ResourceManagers::GetInstance()->GetTexture("TriggerMode.tga");
		m_modeButton->SetTexture(texture);
		m_textTutorial->SetText("Use metal block to trigger all Orange blocks.");
		break;
	case PlayMode::MATH:
		texture = ResourceManagers::GetInstance()->GetTexture("MathMode.tga");
		m_modeButton->SetTexture(texture);
		m_textTutorial->SetText("Let's make the sum of the active block values equal to require value");
		break;
	default:
		break;
	}

	this->choosingModeIndex = newModeIndex;
};

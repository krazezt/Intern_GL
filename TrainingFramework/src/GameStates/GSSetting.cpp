#include "GSSetting.h"
#include "Camera.h"
GSSetting::GSSetting() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}


GSSetting::~GSSetting()
{
}



void GSSetting::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Background3.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// Load all button textures
	texture_musicButton_On = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	texture_musicButton_Off = ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga");
	texture_sfxButton_On = ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga");
	texture_sfxButton_Off = ResourceManagers::GetInstance()->GetTexture("btn_sfx_off.tga");

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	// music setting button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	m_musicButton = std::make_shared<GameButton>(model, shader, texture);
	m_musicButton->Set2DPosition(Globals::screenWidth/2, Globals::screenHeight/2 - 150);
	m_musicButton->SetSize(200, 200);
	if (Globals::music_on) {
		m_musicButton->SetOnClick([this]() {
				this->musicOff();
			});
		m_musicButton->SetTexture(texture_musicButton_On);
	}
	else musicOff();

	m_listButton.push_back(m_musicButton);

	// sfx setting button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga");
	m_sfxButton = std::make_shared<GameButton>(model, shader, texture);
	m_sfxButton->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2 + 150);
	m_sfxButton->SetSize(200, 200);
	if (Globals::sfx_on) this->sfxOn();
	else sfxOff();

	m_listButton.push_back(m_sfxButton);

	// State title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_textGameName = std::make_shared< Text>(shader, font, "Setting", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	m_textGameName->Set2DPosition(Vector2(60, 200));
}

void GSSetting::musicOn() {
	std::string name = "HoYoMIX_Storm_trimmed.mp3";

	m_musicButton->SetTexture(texture_musicButton_On);
	ResourceManagers::GetInstance()->PlaySound(name, true);
	m_musicButton->SetOnClick([this]() {
		this->musicOff();
	});

	Globals::music_on = true;
}

void GSSetting::musicOff() {
	std::string name = "HoYoMIX_Storm_trimmed.mp3";

	m_musicButton->SetTexture(texture_musicButton_Off);
	ResourceManagers::GetInstance()->StopSound(name);
	m_musicButton->SetOnClick([this]() {
		this->musicOn();
	});

	Globals::music_on = false;
}

void GSSetting::sfxOn() {
	m_sfxButton->SetTexture(texture_sfxButton_On);
	m_sfxButton->SetOnClick([this]() {
		this->sfxOff();
	});

	Globals::sfx_on = true;
}

void GSSetting::sfxOff() {
	m_sfxButton->SetTexture(texture_sfxButton_Off);
	m_sfxButton->SetOnClick([this]() {
		this->sfxOn();
	});

	Globals::sfx_on = false;
}

void GSSetting::Exit()
{
}


void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
}


void GSSetting::HandleEvents()
{
}

void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSSetting::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSSetting::HandleMouseMoveEvents(int x, int y)
{
}

void GSSetting::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSSetting::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_textGameName->Draw();
}

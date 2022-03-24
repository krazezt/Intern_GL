#pragma once
#include "GameStateBase.h"
#include "GameButton.h"

class GSSetting :
	public GameStateBase
{
public:
	GSSetting();
	~GSSetting();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;

	void	musicOn();
	void	musicOff();
	void	sfxOn();
	void	sfxOff();

private:
	std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>					m_textGameName;
	std::shared_ptr<GameButton>				m_musicButton;
	std::shared_ptr<GameButton>				m_sfxButton;

	std::shared_ptr<Texture>				texture_musicButton_On;
	std::shared_ptr<Texture>				texture_musicButton_Off;
	std::shared_ptr<Texture>				texture_sfxButton_On;
	std::shared_ptr<Texture>				texture_sfxButton_Off;
};


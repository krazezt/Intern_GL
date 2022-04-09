#pragma once
#include "GameStateBase.h"
#include "GameButton.h"

class GSChooseNumberOfPlayers :
	public GameStateBase
{
public:
	GSChooseNumberOfPlayers();
	~GSChooseNumberOfPlayers();

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

	static int	getNOPlayerCount() { return n_o_player; };

private:
	static int n_o_player;

	std::shared_ptr<Sprite2D>				m_background;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>					m_textGameName;
	std::shared_ptr<Text>					m_textPlayerCount;
	std::shared_ptr<GameButton>				m_moreButton;
	std::shared_ptr<GameButton>				m_lessButton;
	std::shared_ptr<GameButton>				m_playButton;

	int		maxPlayer;
	int		minPlayer;
};


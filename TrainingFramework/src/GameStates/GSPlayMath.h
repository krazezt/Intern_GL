#pragma once
#include "GameStateBase.h"
#include "Actors/Player.h"
#include "Actors/Actor.h"
#include "Terrain/BaseTerrain.h"
#include "CollisionManager.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;

class GSPlayMath :
	public GameStateBase
{
public:
	GSPlayMath();
	~GSPlayMath();

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

	void	checkEndgame();
	void	initRandomSeed();
	int		getRandomValue(int from, int to);
	void	setupNewRound();
	bool	checkEndRound();
	bool	checkEndGame();

private:
	bool	pausing;
	bool	isEnd;
	int		score;
	int		timeLeft;
	float	totalTime;
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score;
	std::shared_ptr<Text>		m_endGame;
	std::shared_ptr<GameButton>	m_pauseButton;
	std::list<std::shared_ptr<Player>>			m_listPlayer;
	std::list<std::shared_ptr<GameButton>>		m_listButton;
	std::list<std::shared_ptr<Actor>>			m_listActor;
	std::list<std::shared_ptr<BaseTerrain>>		m_listTerrain;
};


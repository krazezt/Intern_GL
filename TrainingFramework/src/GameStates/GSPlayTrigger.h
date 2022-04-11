#pragma once
#include "GameStateBase.h"
#include "Actors/Player.h"
#include "Actors/Actor.h"
#include "Terrain/BaseTerrain.h"
#include "CollisionManager.h"
#include "Actors/TriggerBlock.h"
#include "Terrain/Triggerer.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;

class GSPlayTrigger :
	public GameStateBase
{
public:
	GSPlayTrigger();
	~GSPlayTrigger();

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

	void	checkEnd();
	void	initEndgameText();

	int		m_Test;

private:
	bool	pausing;
	bool	isEnd;
	bool	win;
	int		score;
	int		initScore;
	float	totalTime;
	std::shared_ptr<Sprite2D>		m_background;
	std::shared_ptr<Text>			m_score;
	std::shared_ptr<Text>			m_endGame;
	std::shared_ptr<GameButton>		m_pauseButton;
	std::shared_ptr<TriggerBlock>	m_triggerBlock;

	std::list<std::shared_ptr<Player>>			m_listPlayer;
	std::list<std::shared_ptr<GameButton>>		m_listButton;
	std::list<std::shared_ptr<Actor>>			m_listActor;
	std::list<std::shared_ptr<BaseTerrain>>		m_listTerrain;
	std::list<std::shared_ptr<Triggerer>>		m_listTriggerer;
};


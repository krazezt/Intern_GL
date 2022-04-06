#pragma once
#include "GameStateBase.h"
#include "Actors/Player.h"
#include "Actors/Actor.h"
#include "Terrain/BaseTerrain.h"
#include "Terrain/Platform/Platform1.h"
#include "CollisionManager.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

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
	static void	addSpawnedActor(std::shared_ptr<Actor> spawnedActor);
    int m_Test;

private:
	bool	pausing;
	std::shared_ptr<Player>		player;
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_score;
	std::shared_ptr<GameButton>	m_pauseButton;
	std::list<std::shared_ptr<GameButton>>		m_listButton;
	std::list<std::shared_ptr<Actor>>			m_listActor;
	std::list<std::shared_ptr<BaseTerrain>>		m_listTerrain;
	static std::list<std::shared_ptr<Actor>>	m_listSpwActor;
};


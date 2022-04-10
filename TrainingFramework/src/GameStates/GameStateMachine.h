#pragma once
#include "GameManager/Singleton.h"
#include "GameConfig.h"
#include <list>

class GameStateBase;

enum class StateType
{
	STATE_INVALID = 0,
	STATE_INTRO,
	STATE_MENU,
	STATE_PLAY_SURVIVE,
	STATE_PLAY_TRIGGER,
	STATE_SETTING,
	STATE_CHOOSING_MODE,
	STATE_CHOOSING_N_O_PLAYERS,
};

enum class PlayMode {
	INVALID,
	SURVIVE,
	TRIGGER,
};

class GameStateMachine : public CSingleton<GameStateMachine>
{
private:
	PlayMode	choosingMode;
	std::list < std::shared_ptr<GameStateBase>>	m_StateStack;
	std::shared_ptr<GameStateBase>				m_pActiveState;
	std::shared_ptr<GameStateBase>				m_pNextState;
	bool	m_running;
	bool	m_fullscreen;
public:
	GameStateMachine();
	~GameStateMachine();

	void	Cleanup();

	void	ChangeState(std::shared_ptr<GameStateBase> state);
	void	ChangeState(StateType stt);
	void	PushState(StateType stt);
	void	PopState();

	bool	isRunning() { return m_running; }
	void	Quit() { m_running = false; }
	void	PerformStateChange();

	PlayMode	getChoosingMode() { return choosingMode; };
	void		setChoosingMode(PlayMode choosingMode) { this->choosingMode = choosingMode; };
	StateType	getGameStateByMode(PlayMode choosingMode);

	inline std::shared_ptr<GameStateBase> CurrentState()const
	{
		return m_pActiveState;
	}

	inline bool NeedsToChangeState()const
	{
		return (m_pNextState != 0);
	}

	inline bool HasState()const
	{
		return m_StateStack.size() > 0;
	}
};


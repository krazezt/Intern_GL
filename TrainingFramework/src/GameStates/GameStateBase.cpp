/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlaySurvive.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSSetting.h"
#include "GSChoosingMode.h"
#include "GSChooseNumberOfPlayers.h"
#include "GSPlayTrigger.h"

#include "GameStatebase.h"

GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		break;
	case StateType::STATE_PLAY_SURVIVE:
		gs = std::make_shared<GSPlaySurvive>();
		break;
	case StateType::STATE_PLAY_TRIGGER:
		gs = std::make_shared<GSPlayTrigger>();
		break;
	case StateType::STATE_SETTING:
		gs = std::make_shared<GSSetting>();
		break;
	case StateType::STATE_CHOOSING_MODE:
		gs = std::make_shared<GSChoosingMode>();
		break;
	case StateType::STATE_CHOOSING_N_O_PLAYERS:
		gs = std::make_shared<GSChooseNumberOfPlayers>();
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}
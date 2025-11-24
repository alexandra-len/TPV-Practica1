#pragma once
#include "gameState.h"

class PauseState : public GameState
{
public:
	PauseState(Game* g) : GameState(g) {};
};

#pragma once
#include "gameState.h"

class EndState : public GameState
{
public:
	EndState(Game*, bool won);
};


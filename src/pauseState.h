#pragma once
#include "gameState.h"
class PlayState;

class PauseState : public GameState
{
public:
	PauseState(Game* g, PlayState *p);
	void restartGame();
	void render()const override;

private:
	PlayState* playState;
};

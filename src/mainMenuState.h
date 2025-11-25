#pragma once
#include "GameState.h"
#include <SDL3/SDL.h>
#include <vector>

class Button;

class MainMenuState : public GameState
{
public:
    MainMenuState(Game* g) : GameState(g) {};
    ~MainMenuState() = default;

    void handleEvent(const SDL_Event&) override;
};


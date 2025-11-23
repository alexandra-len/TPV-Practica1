#pragma once
#include "GameState.h"
#include <SDL3/SDL.h>
#include <vector>
class Button;

class MainMenuState :public GameState
{
public:
    MainMenuState(Game*);
    ~MainMenuState();
     void handleEvent(const SDL_Event& event) override;
};


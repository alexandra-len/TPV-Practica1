#pragma once
#include "GameState.h"
#include <SDL3/SDL.h>
#include <vector>

class Button;

class MainMenuState : public GameState
{
private:
    std::vector<std::string> maps;
    std::vector<Button> buttons;
    int selectedMap = 0;

public:
    MainMenuState(Game* g) : GameState(g) {};
    ~MainMenuState() = default;

    void handleEvent(const SDL_Event&) override;
};


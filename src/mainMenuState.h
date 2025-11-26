#pragma once
#include "GameState.h"
#include "game.h"
#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <unordered_map>

class Button;

class MainMenuState : public GameState
{
private:
    std::vector<std::string> maps;
    std::vector<Button*> buttons;
    int selectedMap = 0;

public:
    MainMenuState(Game* g);
    ~MainMenuState();

    void handleEvent(const SDL_Event&) override;
};


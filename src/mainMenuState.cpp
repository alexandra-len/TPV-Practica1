#include "mainMenuState.h"
#include "label.h"
#include "button.h"
#include "game.h"
#include "playState.h"
#include "gameStateMachine.h"
#include <filesystem>
#include <fstream>
#include <string>
using namespace std;

static const char* CONFIG_FILE = "config.txt";

MainMenuState::MainMenuState(Game* g) : GameState(g)
{
	ifstream map(CONFIG_FILE);
	if (map.is_open())
		map >> selectedMap;

    // bg
	addObject(new Label(this, game->getTexture(Game::MENU_BACKGROUND),Point2D<int>(0, 0)));
    
    // elegir text
    addObject(new Label(this, game->getTexture(Game::ELEGIR), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::ELEGIR)->getFrameWidth()/2, Game::WINDOW_HEIGHT / 2 - game->getTexture(Game::ELEGIR)->getFrameHeight())));

    Button* exitButton = new Button(this, game->getTexture(Game::SALIR), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::SALIR)->getFrameWidth() / 2, 2 * Game::WINDOW_HEIGHT / 3 + game->getTexture(Game::SALIR)->getFrameHeight()));
    exitButton->connect([this]()
        {
            game->popState();
        });

    addObject(exitButton);

    unordered_map<string, Game::TextureName> mapTextures({
        {"Avispado", Game::AVISPADO},
        {"Original", Game::ORGINIAL},
        {"Practica 1", Game::PRACTICA1},
        {"Trivial", Game::TRIVIAL},
        {"Veloz", Game::VELOZ}
    });

    int i = 0;
    for (auto entry : std::filesystem::directory_iterator("../assets/maps")) {
        string map = entry.path().stem().string();
        maps.push_back(map);

        Button* mapButton = new Button(this, game->getTexture(mapTextures[map]), { Game::WINDOW_WIDTH / 2 - game->getTexture(mapTextures[map])->getFrameWidth() / 2, Game::WINDOW_HEIGHT / 2 + game->getTexture(mapTextures[map])->getFrameHeight() });
        mapButton->connect([this, i]() {game->pushState(new PlayState(game, maps[i])); });
        mapButton->setActive(false);
        
        addObject(mapButton);

        buttons.push_back(mapButton);
        
        i++;
    }
    buttons[selectedMap]->setActive(true);
}


MainMenuState::~MainMenuState()
{
	ofstream map(CONFIG_FILE);
	map << selectedMap;
}

void MainMenuState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);

    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        switch (event.key.key)
        {

        case SDLK_LEFT:
            if (selectedMap-1>= 0)
            {
                buttons[selectedMap]->setActive(false);

                selectedMap--;

                buttons[selectedMap]->setActive(true);
            }
            break;

        case SDLK_RIGHT:
            if (selectedMap+1<buttons.size())
            {
                buttons[selectedMap]->setActive(false);
                selectedMap++;
                buttons[selectedMap]->setActive(true);
            }
            break;

        case SDLK_RETURN:
            break;
        }
    }
}

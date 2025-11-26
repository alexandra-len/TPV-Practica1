#include "mainMenuState.h"
#include "label.h"
#include "button.h"
#include "game.h"
#include "playState.h"
#include "gameStateMachine.h"
#include <filesystem>
#include <fstream>
using namespace std;

static const char* CONFIG_FILE = "config.txt";

MainMenuState::MainMenuState(Game* g) : GameState(game), selectedMap()
{
	ifstream map(CONFIG_FILE);
	if (map.is_open())
		map >> selectedMap;

	addObject(new Label(this, game->getTexture(Game::MENU_BACKGROUND),Point2D<int>(0, 0)));
	//addObject(new Label(this, game->getTexture(Game::ELEGIR),Point2D<int>()));

	Button* exitButton = new Button(this,game->getTexture(Game::SALIR),Point2D<int>());
	exitButton->connect([this]() 
		{
			game->popState();
		});
	addObject(exitButton);
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
            //game->pushState();
            break;
        }
    }
}

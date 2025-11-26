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

	
    //for (auto entry : std::filesystem::directory_iterator("maps"))
    //    cout << entry.path().stem().string() << endl;
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

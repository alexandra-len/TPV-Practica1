#include "pauseState.h"
#include "gameStateMachine.h"
#include "label.h"
#include "button.h"
#include "game.h"
#include "playState.h"
#include <string>

PauseState::PauseState(Game* g, PlayState* p) : GameState(g), playState(p)
{
	//continuar
	Button* continueButton = new Button(this, game->getTexture(Game::CONTINUAR), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::CONTINUAR)->getFrameWidth() / 2, Game::WINDOW_HEIGHT / 5 - game->getTexture(Game::CONTINUAR)->getFrameHeight()));
	continueButton->connect([this]()
		{
			game->popState();
		});
	addObject(continueButton);

	//reiniciar
	Button* restartButton = new Button(this, game->getTexture(Game::REINICIAR), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::REINICIAR)->getFrameWidth() / 2, 2*Game::WINDOW_HEIGHT / 5 - game->getTexture(Game::REINICIAR)->getFrameHeight()));
	restartButton->connect([this]()
		{
			restartGame();
		});
	addObject(restartButton);


	//volver al menu
	Button* returnButton = new Button(this, game->getTexture(Game::VOLVER), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::VOLVER)->getFrameWidth() / 2, 3*Game::WINDOW_HEIGHT / 5 - game->getTexture(Game::VOLVER)->getFrameHeight()));
	returnButton->connect([this]()
		{
			game->popState();
			game->popState();
		});
	addObject(returnButton);

	//salir
	Button* exitButton = new Button(this, game->getTexture(Game::SALIR), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::SALIR)->getFrameWidth() / 2, 4 * Game::WINDOW_HEIGHT / 5 - game->getTexture(Game::SALIR)->getFrameHeight()));
	exitButton->connect([this]()
		{
			game->popState();
			game->popState();
			game->popState();
		});

	addObject(exitButton);
}

void PauseState::restartGame()
{
	const SDL_MessageBoxButtonData buttons[] = {
				{SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancelar"},
				{0, 1, "Reiniciar"} };

	SDL_MessageBoxData boxData = { SDL_MESSAGEBOX_INFORMATION,game->getWindow(),"Reinicar juego","Quieres reiniciar el juego?",2,buttons };

	int button;

	SDL_ShowMessageBox(&boxData, &button);

	if (button == 1) {
		std::string map = playState->getMapName();
		game->popState();
		game->replaceState(new PlayState(game, map));
	}
}

void PauseState::render()const
{
	playState->render();

	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 128);
	SDL_FRect overlay = 
	{
		0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT 
	};
	SDL_RenderFillRect(game->getRenderer(), & overlay);
	GameState::render();
}

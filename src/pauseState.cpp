#include "pauseState.h"
#include "gameStateMachine.h"
#include "label.h"
#include "button.h"
#include "game.h"
#include "PlayState.h"

PauseState::PauseState(Game* g, PlayState* p) : GameState(g), playState(p)
{
	//reiniciar
	addObject(new Label(this, game->getTexture(Game::REINICIAR), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::REINICIAR)->getFrameWidth() / 2, Game::WINDOW_HEIGHT / 2 - game->getTexture(Game::REINICIAR)->getFrameHeight())));
	Button* restartButton = new Button(this, game->getTexture(Game::REINICIAR), Point2D<int>());
	restartButton->connect([this]()
		{
			restartGame();
		});
	addObject(restartButton);

	//continuar
	addObject(new Label(this, game->getTexture(Game::CONTINUAR), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::CONTINUAR)->getFrameWidth() / 2, Game::WINDOW_HEIGHT / 2 - game->getTexture(Game::CONTINUAR)->getFrameHeight())));
	Button* continueButton = new Button(this, game->getTexture(Game::CONTINUAR), Point2D<int>());
	continueButton->connect([this]()
		{
			game->popState();
		});
	addObject(continueButton);

	//volver al menu
	addObject(new Label(this, game->getTexture(Game::VOLVER), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::VOLVER)->getFrameWidth() / 2, Game::WINDOW_HEIGHT / 2 - game->getTexture(Game::VOLVER)->getFrameHeight())));
	Button* returnButton = new Button(this, game->getTexture(Game::VOLVER), Point2D<int>());
	returnButton->connect([this]()
		{
			game->popState();
		});
	addObject(returnButton);

	//salirt
	Button* exitButton = new Button(this, game->getTexture(Game::SALIR), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::SALIR)->getFrameWidth() / 2, 2 * Game::WINDOW_HEIGHT / 3 + game->getTexture(Game::SALIR)->getFrameHeight()));
	exitButton->connect([this]()
		{
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
		game->popState();
		game->replaceState(new PauseState(game, playState));
	}

}

void PauseState::render()const
{
	playState-> render();

	SDL_FRect overlay = 
	{
		0,0,Game::WINDOW_WIDTH,Game::WINDOW_HEIGHT 
	};
	SDL_RenderFillRect(game->getRenderer(), & overlay);
}

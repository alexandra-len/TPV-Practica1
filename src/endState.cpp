#include "endState.h"
#include "game.h"
#include "button.h"
#include <SDL3/SDL.h>

EndState::EndState(Game* g, bool won) : GameState(g) {
	// Background negro
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
	SDL_FRect bg =
	{
		0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT
	};
	SDL_RenderFillRect(game->getRenderer(), &bg);

	// Default: Won
	Texture* textTexture = game->getTexture(Game::GANADO);
	SDL_Color textColor = { 0,255,0 };
	// Se comprueba si ha perdido
	if (!won) {
		textTexture = game->getTexture(Game::GAME_OVER);
		textColor = { 255, 0, 0 };
	}

	addObject(new Label(this, textTexture, Point2D<int>(Game::WINDOW_WIDTH/2 - textTexture->getFrameWidth()/2, Game::WINDOW_HEIGHT/3 - textTexture->getFrameHeight()/2), textColor));

	//volver al menu
	Button* returnButton = new Button(this, game->getTexture(Game::VOLVER), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::VOLVER)->getFrameWidth() / 2,  Game::WINDOW_HEIGHT / 2 - game->getTexture(Game::VOLVER)->getFrameHeight()/2));
	returnButton->connect([this]()
		{
			game->popState();
		});
	addObject(returnButton);

	//salir
	Button* exitButton = new Button(this, game->getTexture(Game::SALIR), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::SALIR)->getFrameWidth() / 2, 2 * Game::WINDOW_HEIGHT / 3 - game->getTexture(Game::SALIR)->getFrameHeight()/2));
	exitButton->connect([this]()
		{
			game->popState();
			game->popState();
		});

	addObject(exitButton);
}

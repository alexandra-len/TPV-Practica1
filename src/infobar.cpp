#include "infobar.h"
#include <SDL3/SDL.h>
#include "gameState.h"
#include "playState.h"
#include "texture.h"
#include "game.h"

InfoBar::InfoBar(GameState* g, Texture* t) : GameObject(g), frogHP(0), frogImg(t) {
	frogWidth = frogImg->getFrameWidth();
	frogHeight = frogImg->getFrameHeight();

	timerHeight = frogHeight;
	timerWidth = Game::WINDOW_WIDTH / 3;

	timerPosX = 2 * Game::WINDOW_WIDTH / 3 - 10;
	timerPosY = Game::WINDOW_HEIGHT - DISTANCE_FROM_BELOW;

	timerOutline = {
		(float)timerPosX,
		(float)timerPosY,
		(float)timerWidth,
		(float)timerHeight / 4
	};
}
void InfoBar::render() const {
	for (int i = 1; i <= frogHP; i++) {
		// Define el rectángulo donde se dibuja la rana
		SDL_FRect destRect = {
			(frogWidth * i)/2,
			Game::WINDOW_HEIGHT - frogHeight,
			(float)frogWidth / 2,
			(float)frogHeight / 2
		};
		frogImg->renderFrame(destRect, 0, 0);
	}
	renderTimer();
}

void InfoBar::renderTimer() const {
	SDL_FRect timerInside = {
		timerPosX,
		timerPosY,
		(float)(timerWidth*(remainingTime / PlayState::TIME_LIMIT)),
		timerHeight/4
	};

	SDL_SetRenderDrawColor(gameS->getGame()->getRenderer(), 255, 255, 255, 255); // Blanco
	SDL_RenderRect(gameS->getGame()->getRenderer(), &timerOutline);
	SDL_RenderRect(gameS->getGame()->getRenderer(), &timerInside);
	SDL_RenderFillRect(gameS->getGame()->getRenderer(), &timerInside);
}


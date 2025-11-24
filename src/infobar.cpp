#include "infobar.h"

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

void InfoBar::update() {
	frogHP = playState->getHP();
}

void InfoBar::renderTimer() const {
	SDL_FRect timerInside = {
		timerPosX,
		timerPosY,
		(float)(timerWidth*((float)playState->getRemainingSeconds() / PlayState::TIME_LIMIT)),
		timerHeight/4
	};

	SDL_SetRenderDrawColor(gameS->getRenderer(), 255, 255, 255, 255); // Blanco
	SDL_RenderRect(gameS->getRenderer(), &timerOutline);
	SDL_RenderRect(gameS->getRenderer(), &timerInside);
	SDL_RenderFillRect(gameS->getRenderer(), &timerInside);
}


#include "infobar.h"

void InfoBar::render() const {
	for (int i = 1; i <= frogHP; i++) {
		// Define el rectángulo donde se dibuja la rana
		SDL_FRect destRect = {
			(width * i)/2,
			Game::WINDOW_HEIGHT - height,
			(float)width / 2,
			(float)height / 2
		};
		frogImg->renderFrame(destRect, 0, 0);
	}
}

void InfoBar::update() {
	frogHP = game->getHP();
}


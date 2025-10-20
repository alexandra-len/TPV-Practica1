#include "wasp.h"

void Wasp::render() const {
	texture->render(SDL_FRect(position.getX(), position.getY(), width, height), 0, nullptr, SDL_FLIP_VERTICAL);
}

void Wasp::update() {
	currentTime = SDL_GetTicks();
	if (currentTime >= deathTime) {
		lives = false;
	}
}

bool Wasp::isAlive() const {
	return lives;
}
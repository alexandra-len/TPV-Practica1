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

Collision Wasp::checkCollision(const SDL_FRect& otherRect) {
	Collision collision(Collision::NONE, { 0, 0 });

	SDL_FRect vehicleRect(position.getX(), position.getY(), width, height);

	if (SDL_HasRectIntersectionFloat(&vehicleRect, &otherRect)) {
		collision.type = Collision::ENEMY;
	}
	return collision;
}
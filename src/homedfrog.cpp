#include "homedfrog.h"
#include <SDL3_image/SDL_image.h>

void HomedFrog::render() {
	SDL_FRect destRect = getRect();
	texture->renderFrame(getRect(), 0, 0);
}

bool HomedFrog::isHome() const {
	return visible;
}

void HomedFrog::setHome() {
	visible = true;
}

int HomedFrog::getX() const {
	return position.getX();
}

SDL_FRect HomedFrog::getRect()
{
	const SDL_FRect destRect = { position.getX(),position.getY(),width, height };
	return destRect;
}

Collision HomedFrog::checkCollision(const SDL_FRect& otherRect) {
	Collision collision(Collision::NONE, { 0, 0 });

	SDL_FRect nestRect(position.getX(), position.getY(), width, height);

	if (SDL_HasRectIntersectionFloat(&nestRect, &otherRect)) {
		if (!visible) {
			collision.type = Collision::HOME;
			visible = true;
		}
		else {
			collision.type = Collision::ENEMY;
		}
	}
	return collision;
}

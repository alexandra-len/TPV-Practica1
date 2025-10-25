#include "homedfrog.h"
#include <SDL3_image/SDL_image.h>

void HomedFrog::render() {
	SDL_FRect destRect = getRect();
	texture->renderFrame(getRect(), 0, 0);
	SDL_SetRenderDrawColor(game->renderer, 255, 255, 0, 255);
	SDL_RenderRect(game->renderer, &destRect);
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

	SDL_FRect vehicleRect(position.getX(), position.getY(), width, height);

	if (SDL_HasRectIntersectionFloat(&vehicleRect, &otherRect)) {
		collision.type = Collision::HOME;
	}
	return collision;
}

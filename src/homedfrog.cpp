#include "homedfrog.h"
#include "collision.h"
#include "playState.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>
using namespace std;

void HomedFrog::render() const {
	if (visible) {
		SDL_FRect destRect = {
			position.getX(),
			position.getY(),
			(float)width,
			(float)height
		};
		texture->renderFrame(destRect, 0, 0);
	}

	//SDL_FRect collisionBox = getBoundingBox();
	//SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255); // Rojo
	//SDL_RenderRect(game->getRenderer(), &collisionBox);
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

SDL_FRect HomedFrog::getBoundingBox() const
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
			playState->occupyNest();
			cout << "collided with invisible frog" << endl;
		}
		else {
			collision.type = Collision::ENEMY;
		}
	}
	return collision;
}

#include "frog.h"

void Frog::render() {
	if (texture != nullptr)
	{
		SDL_FRect destRect = getRect();
		if (lastDirection == Point2D<int>(0, 1))
		{
			texture->renderFrame(destRect, 0, 0, SDL_FLIP_VERTICAL);
		}
		else if (lastDirection == Point2D<int>(0, -1))
		{
			texture->renderFrame(destRect, 0, 0, SDL_FLIP_NONE);
		}
		else if (lastDirection == Point2D<int>(-1, 0))
		{
			texture->renderFrame(destRect, 0, 0,-90, nullptr, SDL_FLIP_NONE);
		}
		else if (lastDirection == Point2D<int>(1, 0))
		{
			texture->renderFrame(destRect, 0, 0, 90, nullptr, SDL_FLIP_NONE);
		}
		else texture->renderFrame(destRect, 0, 0);
	}
}

SDL_FRect Frog::getRect()
{
	const SDL_FRect destRect = { position.getX(),position.getY(),width, height };
	return destRect;
}

void Frog::update() {
}

void Frog::handleEvent(const SDL_Event& event) {
	switch (event.key.key) {
	case SDLK_UP:
		lastDirection = Point2D<int>(0, -1);
		break;
	case SDLK_DOWN:
		lastDirection = Point2D<int>(0, 1);
		break;
	case SDLK_LEFT:
		lastDirection = Point2D<int>(-1, 0);
		break;
	case SDLK_RIGHT:
		lastDirection = Point2D<int>(1, 0);
		break;
	}
	Point2D<int> move = Point2D<int>(lastDirection.getX() * width, lastDirection.getY() * height);
	position = position + move;
}

Point2D<int> Frog::lastDir() {
	return lastDirection;
}
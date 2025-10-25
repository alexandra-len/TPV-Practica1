#include "frog.h"
#include <iostream>
#include <SDL3_image/SDL_image.h>
using namespace std;

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
		SDL_SetRenderDrawColor(game->renderer, 255, 255, 0, 255);
		SDL_RenderRect(game->renderer, &destRect);
	}
}

SDL_FRect Frog::getRect()
{
	const SDL_FRect destRect = { position.getX(),position.getY(),width, height };
	return destRect;
}

void Frog::update() {
	position = Point2D<int>(round(position.getX() + velocity.getX()), position.getY());

	Collision collision;
	collision = game->checkCollision(getRect());
	switch (collision.type) {
		case Collision::ENEMY:
			handleDeath();
			break;
		case Collision::PLATFORM:
			velocity = collision.speed;
			break;
		case Collision::HOME:
			position = initialPos;
			break;
		case Collision::NONE:
			velocity = Vector2D<float>(0, 0);
			if (position.getY() <= Game::RIVER_LOW) {
				handleDeath();
				cout << "river hit";
			}
			break;
	}
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
	Point2D<int> move = Point2D<int>(lastDirection.getX() * width, lastDirection.getY() * 31);
	position = position + move;
}

Point2D<int> Frog::lastDir() const {
	return lastDirection;
}

void Frog::handleDeath() {
	hp--;
	position = initialPos;
	lastDirection = Point2D<int>(0, 0);
	if (hp <= 0) {
		game->exitGame();
	}
}

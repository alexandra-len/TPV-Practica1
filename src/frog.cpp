#include "frog.h"

void Frog::render() {
	texture->render(SDL_FRect(position.getX(), position.getY(), width, height));
}

void Frog::update() {
	Point2D<int> move = Point2D<int>(lastDirection.getX() * width, lastDirection.getY() * height);
	position = position + move;
	lastDirection = Point2D<int>(0, 0);
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
}

Point2D<int> Frog::lastDir() {
	return lastDirection;
}
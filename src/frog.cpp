#include "frog.h"

void Frog::render() {
	texture->render(SDL_FRect(position.getX(), position.getY(), width, height));
}

void Frog::update() {

}

void Frog::handleEvent(const SDL_Event& event) {
	switch (event.key.key) {
	case SDLK_UP:
		position = position + Point2D<int>(0, -height);
		lastDirection = Point2D<int>(0, 1);
	case SDLK_DOWN:
		position = position + Point2D<int>(0, -height);
		lastDirection = Point2D<int>(0, -1);
	case SDLK_LEFT:
		position = position + Point2D<int>(-width, 0);
		lastDirection = Point2D<int>(-1, 0);
	case SDLK_RIGHT:
		position = position + Point2D<int>(width, 0);
		lastDirection = Point2D<int>(1, 0);
	}
}
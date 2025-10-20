#include "homedfrog.h"

void HomedFrog::render() {
	texture->render(SDL_FRect(position.getX(), position.getY(), width, height));
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
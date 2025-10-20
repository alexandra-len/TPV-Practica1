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

Collision HomedFrog::checkCollision(const SDL_FRect& otherRect) {
	Collision collision(Collision::NONE, { 0, 0 });

	SDL_FRect vehicleRect(position.getX(), position.getY(), width, height);

	if (SDL_HasRectIntersectionFloat(&vehicleRect, &otherRect)) {
		collision.type = Collision::HOME;
	}
	return collision;
}
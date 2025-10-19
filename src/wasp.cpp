#include "wasp.h"

void Wasp::render() const {
	if (isAlive()) {
		texture->render(SDL_FRect(position.getX(), position.getY(), width, height));
	}
}

void Wasp::update() {
	if (!isAlive()) return;
	// Movimiento sencillo
	position = Point2D<int>(
		position.getX() + static_cast<int>(speed.getX()),
		position.getY() + static_cast<int>(speed.getY())
	);
}

bool Wasp::isAlive() const {
	Uint32 now = SDL_GetTicks();
	return (now - birthTime) < lifeTime;
}

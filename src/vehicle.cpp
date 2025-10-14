#include "vehicle.h"

void Vehicle::render() const {
	texture->render(SDL_FRect(position.getX(), position.getY(), width, height));
}

void Vehicle::update() {
	position = Point2D<int>(position.getX() + (speed.getX()), position.getY() + speed.getY());

	const int windowWidth = Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN;
	if (speed.getX() > 0 && position.getX() > windowWidth)
	{
		position = Point2D<int>(-width, position.getY());
	}
	else if (speed.getX() < 0 && position.getX() < (-Game::WINDOW_WIDTH_MARGIN))
	{
		position = Point2D<int>(windowWidth, position.getY());
	}
}

Collision Vehicle::checkCollision(const SDL_FRect& otherRect) {
	Collision collision(Collision::NONE, { 0, 0 });

	SDL_FRect vehicleRect(position.getX(), position.getY(), width, height);

	if (SDL_HasRectIntersectionFloat(&vehicleRect, &otherRect)) {
		collision.type = Collision::ENEMY;
	}
	return collision;
}
#include "vehicle.h"
#include <cmath>
#include <SDL3_image/SDL_image.h>

Vehicle::Vehicle(istream input) {

}

void Vehicle::render() const {
	texture->render(SDL_FRect(position.getX(), position.getY(), width, height));
	SDL_SetRenderDrawColor(game->renderer, 255, 255, 0, 255);
	SDL_FRect destRect = SDL_FRect(position.getX(), position.getY(), (width), (height));
	SDL_RenderRect(game->renderer, &destRect);
}

void Vehicle::update() {	
	if (speed.getX() > 0 && position.getX() > windowWidth)
	{
		position = Point2D<int>(-width, position.getY());
	}
	else if (speed.getX() < 0 && position.getX() < (-Game::WINDOW_WIDTH_MARGIN))
	{
		position = Point2D<int>(Game::WINDOW_WIDTH, position.getY());
	}
	else {
		position = Point2D<int>(round(position.getX() + speed.getX()), position.getY());
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

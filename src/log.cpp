#include "log.h"

void Log::render() const
{
	texture->render(SDL_FRect(position.getX(), position.getY(), (width), (height)));
}

void Log::update() 
{
	if (speed.getX() > 0 && position.getX() >= windowWidth)
	{
		position = Point2D<int>(-(Game::WINDOW_WIDTH_MARGIN+width), position.getY());
	}
	else if (speed.getX() < 0 && position.getX() < (-Game::WINDOW_WIDTH_MARGIN))
	{
		position = Point2D<int>(windowWidth, position.getY());
	}
	else {
		position = Point2D<int>(position.getX() + (speed.getX()), position.getY() + speed.getY());
	}
}

Collision Log::checkCollision(const SDL_FRect& otherRect)
{
	Collision collision(Collision::NONE, { 0, 0 });

	SDL_FRect logRect(position.getX(), position.getY(), width, height);

	if (SDL_HasRectIntersectionFloat(&logRect, &otherRect)) 
	{
		collision.type = Collision::PLATFORM;
		collision.speed = speed;
	}

	return collision;
}



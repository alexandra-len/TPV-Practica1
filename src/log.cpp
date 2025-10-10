#include "log.h"

void Log::render() const
{
	texture->render(SDL_FRect(position.getX(), position.getY(), (width), (height)));

	//texture->render();
}

void Log::update() 
{
	position = Point2D<int>( position.getX() + (speed.getX()), position.getY() + speed.getY());

	const int windowWidth = Game::WINDOW_WIDTH;
	if (speed.getX() > 0 && position.getX() > windowWidth)
	{
		position = Point2D<int>(-width, position.getY());
	}
	else if (speed.getX() < 0 && position.getX() < width)
	{
		position = Point2D<int>(windowWidth, position.getY());
	}
}

Collision Log::checkCollision(const SDL_FRect& otherRect)
{
	Collision collision;
	collision.type = Collision::NONE;
	collision.speed = { 0.0f, 0.0f };

	SDL_FRect logRect{static_cast<float>(position.getX()), static_cast<float>(position.getY()),width,height};

	if (SDL_HasRectIntersectionFloat(&logRect, &otherRect)) 
	{
		collision.type = Collision::PLATFORM;
		collision.speed = speed;
	}

	return collision;
}



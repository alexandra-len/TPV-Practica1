#include "log.h"
#include <cmath>
#include <SDL3_image/SDL_image.h>

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


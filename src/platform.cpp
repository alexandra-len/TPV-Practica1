#include "platform.h"
#include "collision.h"

Collision Platform::checkCollision(const SDL_FRect& other) {
	Collision collision(Collision::NONE, { 0, 0 });

	SDL_FRect rect = getBoundingBox();

	if (SDL_HasRectIntersectionFloat(&rect, &other))
	{
		collision.type = Collision::PLATFORM;
		collision.speed = speed;
	}
	return collision;
}

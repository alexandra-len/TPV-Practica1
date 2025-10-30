#pragma once

#include "crosser.h"

class Platform : public Crosser
{
public:
	using Crosser::Crosser;

	Collision checkCollision(SDL_FRect& other) override {
		Collision collision(Collision::NONE, { 0, 0 });

		SDL_FRect logRect(position.getX(), position.getY(), width, height);

		if (SDL_HasRectIntersectionFloat(&logRect, &other))
		{
			collision.type = Collision::PLATFORM;
			collision.speed = speed;
		}
		return collision;
	}
};


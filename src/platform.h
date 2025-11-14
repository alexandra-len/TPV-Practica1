#pragma once

#include "crosser.h"

class Platform : public Crosser
{
public:
	using Crosser::Crosser;

	Collision checkCollision(const SDL_FRect& other) override {
		Collision collision(Collision::NONE, { 0, 0 });

		SDL_FRect rect = getBoundingBox();

		if (SDL_HasRectIntersectionFloat(&rect, &other))
		{
			collision.type = Collision::PLATFORM;
			collision.speed = speed;
		}
		return collision;
	}
};


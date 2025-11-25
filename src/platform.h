#pragma once

#include "crosser.h"

class Platform : public Crosser
{
public:
	using Crosser::Crosser;

	Collision checkCollision(const SDL_FRect& other) override;
};


#pragma once
#include "SDL3/SDL.h"
#include "GameError.h"

class SDLError : public GameError
{
public:
	SDLError() : GameError(SDL_GetError()) {}
};


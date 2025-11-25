#pragma once
#include <SDL3/SDL.h>

class EventHandler 
{
public:
	virtual void handleEvent(const SDL_Event& ev) = 0;
};


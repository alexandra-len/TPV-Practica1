#pragma once
class EventHandler 
{
	virtual void handleEvent(SDL_Event& ev) = 0;
};


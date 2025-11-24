#pragma once
class EventHandler 
{
public:
	virtual void handleEvent(const SDL_Event& ev) = 0;
};


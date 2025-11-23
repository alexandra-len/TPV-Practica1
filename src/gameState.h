#pragma once
#include "GameObject.h"
#include "SDL3/SDL.h"
#include "EventHandler.h"
using DelayedCallback = ;

class GameState
{
    std::list<GameObject*> gameObject;
    std::list<EventHandler*> eventHandler;
    std::list<DelayedCallback> delayedCallback;

public:
    virtual void render() const;
    virtual void update();
    virtual void handleEvent(const SDL_Event&);

    void addEventListener(EventHandler*);
    void addObject(GameObject*);

protected:
    Game* game;
};


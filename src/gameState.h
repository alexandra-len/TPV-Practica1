#pragma once
#include "GameObject.h"
#include "SDL3/SDL.h"
#include "EventHandler.h"
#include <functional>
using DelayedCallback = std::function<void()>;

class GameState
{
    std::list<GameObject*> gameObjects;
    std::list<EventHandler*> eventHandlers;
    std::list<DelayedCallback> delayedCallbacks;

public:
    GameState(Game* g) : game(g) {};
    virtual void render() const;
    virtual void update();
    virtual void handleEvent(const SDL_Event&);

    Game* getGame() const {
        return game;
    }

    void addEventListener(EventHandler*);
    void addObject(GameObject*);

protected:
    Game* game;
};


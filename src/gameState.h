#pragma once
#include "SDL3/SDL.h"
//#include "gameobject.h"
#include "EventHandler.h"

#include <functional>
#include <list>

class Game;
class GameObject;

class GameState
{
    using DelayedCallback = std::function<void()>;

    std::list<GameObject*> gameObjects;
    std::list<EventHandler*> eventHandlers;
    std::list<DelayedCallback> delayedCallbacks;

protected:
    Game* game;

public:
    using Anchor = std::list<GameObject*>::iterator;

    GameState(Game* g);
    virtual ~GameState();
    virtual void render() const;
    virtual void update();
    virtual void handleEvent(const SDL_Event&);

    Game* getGame() const {
        return game;
    }

    void addEventListener(EventHandler*);
    void addObject(GameObject*);

    void runLater(DelayedCallback d);
};


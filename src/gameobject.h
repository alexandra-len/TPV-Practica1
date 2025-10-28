#pragma once

#include "game.h"

class GameObject
{
	Game* game;
protected:
	GameObject(Game* g) : game(g) {}
public:
	virtual ~GameObject() {}

	virtual void render();
	virtual void update();
};


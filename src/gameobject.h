#pragma once

#include "game.h"

class GameObject
{
protected:
	Game* game;

	GameObject() {};
	GameObject(Game* g) : game(g) {}
public:
	virtual ~GameObject() {}

	virtual void render();
	virtual void update();
};


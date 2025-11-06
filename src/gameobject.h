#pragma once

#include "game.h"

class GameObject
{
protected:
	Game* game;

	GameObject() : game(nullptr) {};
	GameObject(Game* g) : game(g) {}
public:
	virtual ~GameObject() {}

	virtual void render() const = 0;
	virtual void update() = 0;
};

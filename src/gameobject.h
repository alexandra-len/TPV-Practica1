#pragma once

#include "game.h"

class GameObject
{
protected:
	GameState* game;

	GameObject() : game(nullptr) {};
	GameObject(GameState* g) : game(g) {}
public:
	virtual ~GameObject() {}

	virtual void render() const = 0;
	virtual void update() = 0;
};

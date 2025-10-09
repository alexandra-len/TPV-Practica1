#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"

class Vehicle
{
	Game* game;
	Texture* texture;
	Point2D<int> position;
	Vector2D<float> speed;

public:
	Vehicle(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s) : game(g), texture(t), position(p), speed(s) { }

	void render() const { }
	void update() {	}

	Collision checkCollision(const SDL_FRect&) { }
};
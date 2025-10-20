#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include <SDL3/SDL.h>

class Wasp
{
	Game* game;
	Texture* texture;
	Point2D<int> position;
	Vector2D<float> speed;
	bool lives;
	int width;
	int height;
	int lifetime;
	int deathTime;
	int currentTime;

public:
	Wasp(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s, int l)
		: game(g), texture(t), position(p), speed(s), lifetime(l), deathTime(SDL_GetTicks() + lifetime), currentTime(0), lives(true)
	{
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	}

	void update();
	void render() const;
	bool isAlive() const;
};

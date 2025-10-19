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
	int width;
	int height;
	//int lifeTime;
	Uint32 birthTime;   // momento en que nació
	Uint32 lifeTime;    // duración de vida en ms

public:
	Wasp(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s, Uint32 life)
		: game(g), texture(t), position(p), speed(s), birthTime(SDL_GetTicks()), lifeTime(life)
	{
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	}

	void update();
	void render() const;
	bool isAlive() const;
};

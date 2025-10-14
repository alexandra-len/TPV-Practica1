#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "homedfrog.h"

class Frog
{
	Game* game;
	Texture* texture;
	Point2D<int> position;
	Point2D<int> lastDirection;
	int hp;
	int width;
	int height;

public:
	Frog(Game* g, Texture* t, Point2D<int> p) : game(g), texture(t), position(p), lastDirection(Point2D<int>(0, 1)), hp(3) {
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	};

	void render();
	void update();

	void handleEvent(const SDL_Event&);
};
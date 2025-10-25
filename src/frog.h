#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "homedfrog.h"

class Frog
{
	Game* game;
	Texture* texture;
	Point2D<int> initialPos;
	Point2D<int> position;
	Point2D<int> lastDirection;
	Vector2D<float> velocity;
	int hp;
	int width;
	int height;

	SDL_FRect getRect();
	void handleDeath();

public:
	Frog(Game* g, Texture* t, Point2D<int> p) : game(g), texture(t), initialPos(p), position(p), lastDirection(Point2D<int>(0, 0)), velocity(Vector2D<float>(0, 0)), hp(3) {
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	};

	void render();
	void update();
	Point2D<int> lastDir() const;
	void handleEvent(const SDL_Event&);
};

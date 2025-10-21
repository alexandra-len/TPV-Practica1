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
	Point2D<int> velocity;
	int hp;
	int width;
	int height;

	SDL_FRect getRect();

public:
	Frog(Game* g, Texture* t, Point2D<int> p) : game(g), texture(t), position(p), lastDirection(Point2D<int>(0, 0)), velocity(Point2D<int>(0, 0)), hp(3) {
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	};

	void render();
	void update();
	Point2D<int> lastDir() const;
	void handleEvent(const SDL_Event&);
	void setVelocity(const Point2D<int>& vel) { velocity = vel; }
	Point2D<int> getVelocity() const { return velocity; }
};

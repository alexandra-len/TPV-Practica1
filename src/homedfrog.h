#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"

class HomedFrog
{
	Game* game;
	Texture* texture;
	Point2D<int> position;
	int width;
	int height;
	bool visible;

public:
	HomedFrog(Game* g, Texture* t, Point2D<int> p) : game(g), texture(t), position(p), visible(false) {
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	};

	void render();
	bool isHome() const;
	void setHome();
	int getX() const;
};
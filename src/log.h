#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"

class Log
{
	Game* game;
	Texture* texture;
	Point2D<int> position;
	Vector2D<float> speed;
	int width;
	int height;
	int windowWidth;

public:

	Log(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s) : game(g), texture(t), position(p) {
		speed = Vector2D<float>((float)(s.getX()) / Game::FRAME_RATE, (float) (s.getY()) / Game::FRAME_RATE);
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
		windowWidth = Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN - width;
	}

	void render() const;
	void update();

	Collision checkCollision(const SDL_FRect& otherRect);
};


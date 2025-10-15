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

public:

	Log(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s) : game(g), texture(t), position(p) {
		speed = Vector2D<float>(static_cast<float>(s.getX()) / Game::FRAME_RATE, static_cast<float>(s.getY()) / Game::FRAME_RATE);
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	}

	void render() const;
	void update();

	Collision checkCollision(const SDL_FRect& otherRect);
};


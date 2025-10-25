#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
using namespace std;

class Vehicle
{
	Game* game;
	Texture* texture;
	Point2D<int> position;
	Vector2D<float> speed;
	int width;
	int height;
	int windowWidth;

public:
	Vehicle(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s) : game(g), texture(t), position(p) {
		speed = Vector2D<float>(s.getX() / Game::FRAME_RATE, static_cast<float>(s.getY()) / Game::FRAME_RATE);
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
		windowWidth = Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN - width;
	}
	Vehicle(istream);

	void render() const;
	void update();

	Collision checkCollision(const SDL_FRect&);
};

#pragma once
#include "platform.h"
#include <iostream>

class TurtleGroup : public Platform
{
	int numTurtles;
	bool sinks;

	int frame;
public:
	TurtleGroup(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s) : Platform(g, t, p, s, t->getFrameWidth()) {};
	TurtleGroup(GameState* g, std::istream& input) : Platform(g) {
		int textureNr, x, y, sink;
		float s;
		if (!(input >> x >> y >> s >> numTurtles >> sink)) {
			throw FileFormatError(MAP_FILE);
		}

		position = Point2D<int>(x, y);
		speed = Vector2D<float>(s / Game::FRAME_RATE, 0);

		sinks = sink == 1;

		texture = game->getTexture(Game::TURTLES);
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();

		backjump = texture->getFrameWidth();
	};

	void render() const override;
	void update() override;
	SDL_FRect getBoundingBox() const override;
};


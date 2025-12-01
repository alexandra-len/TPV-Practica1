#pragma once
#include "platform.h"
#include "texture.h"
#include "vector2D.h"
#include <iostream>
#include "vector2D.h"
#include "game.h"

class Game;
struct Collision;

class TurtleGroup : public Platform
{
	static constexpr int TURTLE_SINK_RATE = 225;
	static constexpr int TURTLE_SINK_FRAMES = 7;
	static constexpr int TURTLE_STATIC_FRAMES = 2;

	int numTurtles;
	bool sinks;

	int frame = 0;
public:
	TurtleGroup(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s) : Platform(g, t, p, s, t->getFrameWidth()), frame(0) {};
	TurtleGroup(GameState* g, std::istream& input);

	void render() const override;
	void update() override;
	SDL_FRect getBoundingBox() const override;
};


#pragma once
#include "platform.h"
#include "texture.h"
#include "vector2D.h"
#include <iostream>
#include "vector2D.h"
#include "game.h"

class Game;
struct Collision;

class Game;
struct Collision;

class TurtleGroup : public Platform
{
	int numTurtles;
	bool sinks;

	int frame;
public:
	TurtleGroup(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s) : Platform(g, t, p, s, t->getFrameWidth()) {};
	TurtleGroup(GameState* g, std::istream& input) : Platform(g);

	void render() const override;
	void update() override;
	SDL_FRect getBoundingBox() const override;
};


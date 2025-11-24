#pragma once
#include "gameobject.h"
class Label : public GameObject
{
	Texture* texture;
	Point2D<int> position;

public:
	Label(GameState* g, Texture* t, Point2D<int> p) : GameObject(g), texture(t), position(p) {};
};


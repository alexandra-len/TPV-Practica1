#pragma once
#include "gameobject.h"
#include "vector2D.h"
#include "texture.h"

class Label : public GameObject
{
	Texture* texture;
	Point2D<int> position;

public:
	Label(GameState* g, Texture* t, Point2D<int> p) : GameObject(g), texture(t), position(p) {};
	virtual ~Label() = default;
	void render() const override;
	void update() override;
};


#pragma once
#include "gameobject.h"
#include "vector2D.h"
#include "texture.h"
#include "SDL3/SDL.h"

class Label : public GameObject
{
public:
	Label(GameState* g, Texture* t, Point2D<int> p);
	virtual ~Label() {};
	void render() const override;
	void update() override;
protected:
	Texture* texture;
	Point2D<int> position;

};


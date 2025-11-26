#pragma once

#include "sceneobject.h"
#include "FileFormatError.h"
#include "vector2D.h"
#include <iostream>
#include "vector2D.h"

class Crosser : public SceneObject
{
public: 
	Crosser(GameState*);
	Crosser(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s, int bj);
									
	Crosser(GameState* g, std::istream& input, int textureNrOffset, int bj);

	void update() override;

protected:
	Vector2D<float> speed;
	int backjump;

};


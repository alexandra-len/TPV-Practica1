#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "crosser.h"
#include "platform.h"
#include <istream>

/**
* Clase log que representa un tronco flotante sobre el que la rana puede subirse
*/
class Log : public Platform
{
public:
	//Constructor del tronco
	Log(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s) : Platform(g, t, p, s, t->getFrameWidth()) {};

	Log(Game* g, std::istream& input) : Platform(g, input, Game::LOG1_TEXTURE_NR) {};
};


#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "crosser.h"
#include "platform.h"
#include <istream>
#include "playState.h"

/**
* Clase log que representa un tronco flotante sobre el que la rana puede subirse
*/
class Log : public Platform
{
public:
	//Constructor del tronco
	Log(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s) : Platform(g, t, p, s, t->getFrameWidth()) {};

	Log(GameState* g, std::istream& input) : Platform(g, input, PlayState::LOG1_TEXTURE_NR) {};
};


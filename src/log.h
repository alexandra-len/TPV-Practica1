#pragma once

#include "texture.h"
#include "vector2D.h"
#include "platform.h"
#include <istream>
#include "playState.h"

class GameState;
struct Collision;

/**
* Clase log que representa un tronco flotante sobre el que la rana puede subirse
*/
class Log : public Platform
{
	static constexpr int LOG1_TEXTURE_NR = 7;

public:
	//Constructor del tronco
	Log(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s);

	Log(GameState* g, std::istream& input);
};


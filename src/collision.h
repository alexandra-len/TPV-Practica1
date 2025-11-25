#pragma once
#include "vector2D.h"

// Estructura que representa una colisión
struct Collision
{
	enum Type {
		NONE,
		ENEMY,
		PLATFORM,
		HOME
	};

	Type type;
	Vector2D<float> speed;
};

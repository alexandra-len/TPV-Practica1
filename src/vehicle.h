#pragma once
#include "texture.h"
#include "vector2D.h"
#include "crosser.h"
#include <istream>

class Game;
struct Collision;

class Vehicle : public Crosser
{

	static constexpr int VEHICLE1_TEXTURE_NR = 1;

public:
	// Constructor que inicializa el vehículo
	Vehicle(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s) : Crosser(g, t, p, s, PlayState::VEHICLE_BACKJUMP) {
	}

	//Constructor que carga un vehiculo desde el archivo
	Vehicle(GameState* g, std::istream& input) : Crosser(g, input, VEHICLE1_TEXTURE_NR, PlayState::VEHICLE_BACKJUMP) {}

	//Verifica colisiones
	Collision checkCollision(const SDL_FRect& otherRect) override;
};

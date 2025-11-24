#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "crosser.h"
#include <istream>

class Vehicle : public Crosser
{

public:
	// Constructor que inicializa el vehículo
	Vehicle(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s) : Crosser(g, t, p, s, Game::VEHICLE_BACKJUMP) {
	}

	//Constructor que carga un vehiculo desde el archivo
	Vehicle(GameState* g, std::istream& input) : Crosser(g, input, Game::VEHICLE1_TEXTURE_NR, Game::VEHICLE_BACKJUMP) {}

	//Verifica colisiones
	Collision checkCollision(const SDL_FRect& otherRect) override;
};

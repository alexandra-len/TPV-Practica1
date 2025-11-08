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
	Vehicle(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s) : Crosser(g, t, p, s, Game::VEHICLE_BACKJUMP) {
	}

	//Constructor que carga un vehiculo desde el archivo
	Vehicle(Game* g, std::istream& input) : Crosser(g, input, Game::VEHICLE1_TEXTURE_NR, Game::VEHICLE_BACKJUMP) {}

	//Verifica colisiones
	Collision checkCollision(const SDL_FRect& otherRect) override {
		Collision collision(Collision::NONE, { 0, 0 });

		// Define el rectángulo del vehículo
		SDL_FRect vehicleRect(position.getX(), position.getY(), width, height);

		if (SDL_HasRectIntersectionFloat(&vehicleRect, &otherRect)) {
			collision.type = Collision::ENEMY;
		}
		return collision;
	}
};

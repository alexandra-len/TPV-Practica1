#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "crosser.h"
#include <istream>

class Vehicle : public Crosser
{
	Game* game;
	Texture* texture;
	Point2D<int> position;
	Vector2D<float> speed;
	int width;
	int height;
	int windowWidth;

public:

	// Constructor que inicializa el vehículo
	Vehicle(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s) : Crosser(g, t, p, s) {
	}

	//Constructor que carga un vehiculo desde el archivo
	Vehicle(Game* g, std::istream& input) {
		game = g;
		int textureNr, x, y;
		float s;
		input >> x >> y >> s >> textureNr;

		position = Point2D<int>(x, y);
		speed = Vector2D<float>(s / Game::FRAME_RATE, 0);
		texture = game->getTexture((Game::TextureName)(textureNr + Game::VEHICLE1));

		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
		windowWidth = Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN - width;
	}

	//Renderiza el vehiculo
	void render() const;

	//Actualiza vehiculo
	void update();

	//Verifica colisiones
	Collision checkCollision(const SDL_FRect&);
};

#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include <istream>

class Vehicle
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
	Vehicle(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s) : game(g), texture(t), position(p) {

		// La velocidad ajustada al frame rate
		speed = Vector2D<float>(s.getX() / Game::FRAME_RATE, s.getY() / Game::FRAME_RATE);

		width = texture->getFrameWidth();
		height = texture->getFrameHeight();

		// Calcula el limite lateral donde el vehiculo debe reaparecer
		windowWidth = Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN - width;
	}

	//Constructor que carga un vehiculo desde el archivo
	Vehicle(Game* g, std::istream& input) {
		game = g;
		int textureNr, x, y, s;
		input >> x >> y >> s >> textureNr;

		position = Point2D<int>(x, y);
		speed = Vector2D<float>(s / Game::FRAME_RATE, 0);
		texture = game->getTexture((Game::TextureName)(textureNr + 1));

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

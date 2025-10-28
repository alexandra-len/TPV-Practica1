#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include <istream>

/**
* Clase log que representa un tronco flotante sobre el que la rana puede subirse
*/
class Log
{
	//Atributos privados
	Game* game;
	Texture* texture;
	Point2D<int> position;
	Vector2D<float> speed;
	int width;
	int height;
	int windowWidth;

public:
	//Constructor del tronco
	Log(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s) : game(g), texture(t), position(p) {
		// Normaliza la velocidad a la tasa de frames
		speed = Vector2D<float>((float)(s.getX()) / Game::FRAME_RATE, (float) (s.getY()) / Game::FRAME_RATE);
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
		windowWidth = Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN - width;
	}

	Log(Game* g, std::istream& input) {
		game = g;
		int textureNr, x, y;
		float s;
		input >> x >> y >> s >> textureNr;

		position = Point2D<int>(x, y);
		speed = Vector2D<float>(s / Game::FRAME_RATE, 0);
		texture = game->getTexture((Game::TextureName)(textureNr + 7));

		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
		windowWidth = Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN - width;
	}

	void render() const;

	//Actualiza la posici�n del tronco en cada frame
	void update();
	
	//Comprueba si el tronco colisiona con la rana
	Collision checkCollision(const SDL_FRect& otherRect);
};


#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "homedfrog.h"
using namespace std;

/**
* Clase que representa la rana controlada por el jugador
*/
class Frog
{
	Game* game;
	Texture* texture;
	Point2D<int> initialPos;
	Point2D<int> position;
	Point2D<int> lastDirection;
	Vector2D<float> velocity;
	int hp;
	int width;
	int height;

	SDL_FRect getRect();
	void hurt();

public:
	//Constructor
	Frog(Game* g, Texture* t, Point2D<int> p) : game(g), texture(t), initialPos(p), position(p), lastDirection(Point2D<int>(0, 0)), velocity(Vector2D<float>(0, 0)), hp(3) {
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	};

	//Constructor que carga posicion desde un archivo
	Frog(Game* g, istream& input) : hp(3), velocity(Vector2D<float>(0,0)), lastDirection(Point2D<int>(0,0)) {
		game = g;
		texture = game->getTexture(Game::TextureName::FROG);

		// Lee las coordenadas de inicio desde un fichero
		int x, y;
		input >> x >> y;

		initialPos = position = Point2D<int>(x, y);

		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	}

	//Constantes
	static constexpr int TILE_SIZE = 32;
	static constexpr int FROG_COLLISION_MARGIN = 8;

	void render();
	void update();
	Point2D<int> lastDir() const;
	void handleEvent(const SDL_Event&);
};

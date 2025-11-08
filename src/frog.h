#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "homedfrog.h"
#include "sceneobject.h"

/**
* Clase que representa la rana controlada por el jugador
*/
class Frog : public SceneObject
{
	Point2D<int> initialPos;
	Point2D<int> lastDirection;
	Point2D<int> velocity;
	int hp;

	SDL_FRect getRect();
	void hurt();

public:
	//Constructor
	Frog(Game* g, Texture* t, Point2D<int> p) : initialPos(p), lastDirection(Point2D<int>(0, 0)), velocity(Point2D<int>(0,0)), hp(3), SceneObject(g, t, p) {}

	//Constructor que carga posicion desde un archivo
	Frog(Game* g, std::istream& input) : lastDirection(Point2D<int>(0,0)), SceneObject(g) {
		game = g;
		texture = game->getTexture(Game::TextureName::FROG);

		// Lee las coordenadas de inicio desde un fichero
		int x, y, lives;
		input >> x >> y >> lives;

		initialPos = position = Point2D<int>(x, y);
		hp = lives;
	}

	void render();
	void update();
	Point2D<int> lastDir() const;
	void handleEvent(const SDL_Event&);

	int getHP() const {
		return hp;
	}
};

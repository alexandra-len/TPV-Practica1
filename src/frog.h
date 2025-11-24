#pragma once

#include "texture.h"
#include "vector2D.h"
#include "homedfrog.h"
#include "sceneobject.h"
#include "FileFormatError.h"
#include "eventHandler.h"

/**
* Clase que representa la rana controlada por el jugador
*/
class Frog : public SceneObject, public EventHandler
{
	Point2D<int> initialPos;
	Point2D<int> lastDirection, moveDirection;
	Vector2D<float> velocity;
	int hp;
	PlayState::Anchor anchor;
	void hurt();

	SDL_FRect getBoundingBox() const override;

public:
	//Constructor
	Frog(GameState* g, Texture* t, Point2D<int> p) : initialPos(p), lastDirection(Point2D<int>(0, 0)), velocity(Vector2D<float>(0,0)), hp(3), SceneObject(g, t, p) {}

	//Constructor que carga posicion desde un archivo
	Frog(GameState* g, std::istream& input) : SceneObject(g, g->getGame()->getTexture(Game::TextureName::FROG)), lastDirection(Point2D<int>(0, 0)) {
		// Lee las coordenadas de inicio desde un fichero
		int x, y, lives;
		if (!(input >> x >> y >> lives)) {
			throw FileFormatError(MAP_FILE);
		}

		initialPos = position = Point2D<int>(x, y);
		hp = lives;

		// Transmite al juego el numero de vidas totales que tiene.
		playState->setHP(hp);
	}

	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event&) override;

	void onTimeEnd();

	int getHP() const {
		return hp;
	}

	void setAnchor(PlayState::Anchor a) {
		anchor = a;
	}

	Collision checkCollision(const SDL_FRect& other) override;
};

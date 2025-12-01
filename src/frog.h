#pragma once

#include "texture.h"
#include "vector2D.h"
#include "homedfrog.h"
#include "sceneobject.h"
#include "FileFormatError.h"
#include "eventHandler.h"

class Game;
struct Collision;

/**
* Clase que representa la rana controlada por el jugador
*/
class Frog : public SceneObject, public EventHandler
{
	static constexpr int TILE_SIZE = 32;
	static constexpr int FROG_COLLISION_MARGIN = 8;

	Point2D<int> initialPos;
	Point2D<int> lastDirection, moveDirection;
	Vector2D<float> velocity;
	int hp;
	void hurt();

	SDL_FRect getBoundingBox() const override;

public:
	//Constructor
	Frog(GameState* g, Texture* t, Point2D<int> p);

	//Constructor que carga posicion desde un archivo
	Frog(GameState* g, std::istream& input);

	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event&) override;

	void onTimeEnd();

	int getHP() const {
		return hp;
	}

	Collision checkCollision(const SDL_FRect& other) override;
};

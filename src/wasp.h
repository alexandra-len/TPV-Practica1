#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include <SDL3/SDL.h>
#include "sceneobject.h"

/**
* Clase que representa una avispa enemiga que aparece temporalmente en la mapa
*/
class Wasp : public SceneObject
{
	//Atributos privados
	Game* game;
	Texture* texture;
	Point2D<int> position;
	Vector2D<float> speed;
	bool lives;
	int width;
	int height;
	int lifetime;
	int deathTime;
	int currentTime;
	Game::Anchor anchor;

public:
	//Constructor de la clase
	Wasp(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s, int l)
		: SceneObject(g, t, p), speed(s), lifetime(l), deathTime(SDL_GetTicks() + lifetime), currentTime(0), lives(true)
	{	}

	//Actualiza el estado de la avispa
	void update() override;
	//Comprueba si la avispa sigue viva
	bool isAlive() const;
	void setAnchor(Game::Anchor a) {
		anchor = a;
	}
	//Comprueba si la avispa colisiona con la rana
	Collision checkCollision(const SDL_FRect&);
};

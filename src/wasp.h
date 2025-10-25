#pragma once

#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include <SDL3/SDL.h>

/**
* Clase que representa una avispa enemiga que aparece temporalmente en la mapa
*/
class Wasp
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

public:
	//Constructor de la clase
	Wasp(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s, int l)
		: game(g), texture(t), position(p), speed(s), lifetime(l), deathTime(SDL_GetTicks() + lifetime), currentTime(0), lives(true)
	{
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	}

	//Actualiza el estado de la avispa
	void update();
	//Renderiza la avispa
	void render() const;
	//Comprueba si la avispa sigue viva
	bool isAlive() const;
	//Comprueba si la avispa colisiona con la rana
	Collision checkCollision(const SDL_FRect&);
};

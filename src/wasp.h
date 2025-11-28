#pragma once

#include "texture.h"
#include "vector2D.h"
#include <SDL3/SDL.h>
#include "sceneobject.h"
#include "playState.h"
#include <iostream>

class Game;
struct Collision;

/**
* Clase que representa una avispa enemiga que aparece temporalmente en la mapa
*/
class Wasp : public SceneObject
{
	//Atributos privados
	Vector2D<float> speed;
	bool lives;
	int lifetime;
	int deathTime;
	int currentTime;
	int nestNr;
	PlayState::Anchor playAnchor;
	GameState::Anchor gameAnchor;

public:
	//Constructor de la clase
	Wasp(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s, int l, int n);
	Wasp(GameState* g, std::istream& input);

	void render() const override;
	//Actualiza el estado de la avispa
	void update() override;
	//Comprueba si la avispa sigue viva
	bool isAlive() const;
	void setPlayAnchor(PlayState::Anchor a);
	void setGameAnchor(GameState::Anchor a);
	void destroyWasp();
	//Comprueba si la avispa colisiona con la rana
	Collision checkCollision(const SDL_FRect&) override;
};

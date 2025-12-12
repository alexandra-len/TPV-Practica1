#pragma once
#include "texture.h"
#include "vector2D.h"
#include "sceneobject.h"

struct Collision;

class HomedFrog : public SceneObject
{
	bool visible;// Indica si la rana ya está visible en este nido

public:
	HomedFrog(GameState* g, Texture* t, Point2D<int> p) : SceneObject(g, t, p), visible(false) {};

	void render() const override;
	bool isHome() const; //Comprueba si este nido está ocupado.
	void setHome();// Marca el nido como ocupado y la rana como visible
	int getX() const;
	SDL_FRect getBoundingBox() const override;// Devuelve la caja de colisión
	Collision checkCollision(const SDL_FRect&) override;
};

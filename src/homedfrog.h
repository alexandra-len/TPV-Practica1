#pragma once
#include "game.h"
#include "texture.h"
#include "vector2D.h"
#include "sceneobject.h"

class HomedFrog : public SceneObject
{
	bool visible;

public:
	HomedFrog(Game* g, Texture* t, Point2D<int> p) : SceneObject(g, t, p), visible(false) {};

	void render() const override;
	bool isHome() const;
	void setHome();
	int getX() const;
	SDL_FRect getBoundingBox() const override;
	Collision checkCollision(const SDL_FRect&) override;
};

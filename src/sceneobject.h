#pragma once
#include "gameobject.h"
#include "texture.h"
#include "vector2D.h"
#include "SDL3/SDL.h"
#include "playState.h"

//class PlayState;
struct Collision;

class SceneObject : public GameObject
{
public:
	SceneObject(GameState* g);
	SceneObject(GameState* g, Texture* t);
	SceneObject(GameState* g, Texture* t, Point2D<int> p);

	void render() const override;

	void update() override {};

	virtual Collision checkCollision(const SDL_FRect& other) = 0;

protected:
	PlayState* playState;
	Point2D<int> position = Point2D<int>(0,0);
	Texture* texture = nullptr;
	int width = 0;
	int height = 0;
	

	virtual SDL_FRect getBoundingBox() const {
		return SDL_FRect(position.getX(), position.getY(), width, height);
	}
};


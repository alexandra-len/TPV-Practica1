#pragma once
#include "gameobject.h"
#include "texture.h"

class SceneObject : public GameObject
{

public:
	SceneObject(Game* g, Texture* t, Point2D<int> p) : GameObject(g), texture(t), position(p) {
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	}
	void render() override {
		texture->render(SDL_FRect(position.getX(), position.getY(), width, height));
	}

	virtual Collision checkCollision(SDL_FRect& other);

protected:
	Point2D<int> position;
	int width;
	int height;
	Texture* texture;

	SDL_FRect getBoundingBox() {
		return SDL_FRect(position.getX(), position.getY(), width, height);
	}
};


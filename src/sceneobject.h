#pragma once
#include "gameobject.h"
#include "texture.h"

class SceneObject : public GameObject
{

public:
	SceneObject() {};
	SceneObject(Game* g) : GameObject(g) {};
	SceneObject(Game* g, Texture* t, Point2D<int> p) : GameObject(g), texture(t), position(p) {
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	}

	void render() const override {
		texture->render(SDL_FRect(position.getX(), position.getY(), width, height));
	}

	void update() override {};

	virtual Collision checkCollision(const SDL_FRect& other) {
		return Collision(Collision::NONE, { 0, 0 });
	}

protected:
	Point2D<int> position = Point2D<int>(0,0);
	Texture* texture = nullptr;
	int width = 0;
	int height = 0;
	

	SDL_FRect getBoundingBox() {
		return SDL_FRect(position.getX(), position.getY(), width, height);
	}
};


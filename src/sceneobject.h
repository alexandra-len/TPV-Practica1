#pragma once
#include "gameobject.h"
#include "texture.h"

class PlayState;

class SceneObject : public GameObject
{
public:
	SceneObject() {};
	SceneObject(GameState* g) : GameObject(g) {
		playState = static_cast<PlayState*>(g);
	};
	SceneObject(GameState* g, Texture* t) : GameObject(g), texture(t) {
		playState = static_cast<PlayState*>(g);

		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	};
	SceneObject(GameState* g, Texture* t, Point2D<int> p) : GameObject(g), texture(t), position(p) {
		playState = static_cast<PlayState*>(g);

		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	}

	void render() const override {
		if (texture != nullptr) {
			SDL_FRect destRect = {
				position.getX(),
				position.getY(),
				width,
				height
			};
			texture->render(destRect);
		}

		//SDL_FRect collisionBox = getBoundingBox();
		//SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255); // Rojo
		//SDL_RenderRect(game->getRenderer(), &collisionBox);
	}

	void update() override {};

	virtual Collision checkCollision(const SDL_FRect& other) {
		return Collision(Collision::NONE, { 0, 0 });
	}

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


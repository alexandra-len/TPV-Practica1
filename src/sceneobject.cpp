#include "sceneobject.h"
#include "gameobject.h"
#include "gameState.h"
#include "playState.h"

SceneObject::SceneObject(GameState* g) : GameObject(g) {
	playState = static_cast<PlayState*>(g);
}

SceneObject::SceneObject(GameState* g, Texture* t) : GameObject(g), texture(t) {
	playState = static_cast<PlayState*>(g);

	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
};

SceneObject::SceneObject(GameState* g, Texture* t, Point2D<int> p) : GameObject(g), position(p), texture(t) {
	playState = static_cast<PlayState*>(g);

	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
}

void SceneObject::render() const  {
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

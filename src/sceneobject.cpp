#include "sceneobject.h"
#include "gameobject.h"
#include "gameState.h"
#include "playState.h"

SceneObject::SceneObject(GameState* g, Texture* t, Point2D<int> p) : GameObject(g), texture(t), position(p) {
	playState = static_cast<PlayState*>(g);

	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
}

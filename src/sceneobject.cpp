#include "sceneobject.h"
#include "gameobject.h"
#include "gameState.h"
#include "playState.h"

// Constructor base: Inicializa el puntero a PlayState
SceneObject::SceneObject(GameState* g) : GameObject(g) {
	playState = static_cast<PlayState*>(g);
}
// Constructor con textura: Inicializa la textura y obtiene dimensiones
SceneObject::SceneObject(GameState* g, Texture* t) : GameObject(g), texture(t) {
	playState = static_cast<PlayState*>(g);

	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
};
// Constructor completo: Inicializa posición, textura y dimensiones.
SceneObject::SceneObject(GameState* g, Texture* t, Point2D<int> p) : GameObject(g), position(p), texture(t) {
	playState = static_cast<PlayState*>(g);

	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
}
// Renderizado por defecto: Dibuja la textura en la posición y dimensiones del objeto
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
	// Código de Debug
	//SDL_FRect collisionBox = getBoundingBox();
	//SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255); // Rojo
	//SDL_RenderRect(game->getRenderer(), &collisionBox);
}

#include "gameState.h"

void GameState::render() const {
	for (GameObject* g : gameObjects) {
		g->render();
	}
}

void GameState::update() {
	for (GameObject* g : gameObjects) {
		g->update();
	}
}

void GameState::handleEvent(const SDL_Event& ev) {
	for (EventHandler* e : eventHandlers) {
		e->handleEvent(ev);
	}
}

void GameState::addEventListener(EventHandler* evH) {

}

void GameState::addObject(GameObject* g) {
	gameObjects.push_back(g);
}

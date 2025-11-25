#include "gameState.h"
#include "game.h"
#include "gameobject.h"

GameState::GameState(Game* g) {
	game = g;
};

GameState::~GameState() {
	for (GameObject* g : gameObjects) {
		delete g;
	}
}

void GameState::render() const {
	SDL_RenderClear(game->getRenderer());

	for (GameObject* g : gameObjects) {
		g->render();
	}

	SDL_RenderPresent(game->getRenderer());
}

void GameState::update() {
	for (GameObject* g : gameObjects) {
		g->update();
	}
	for (DelayedCallback c : delayedCallbacks) {
		c();
	}
	delayedCallbacks.clear();
}

void GameState::handleEvent(const SDL_Event& ev) {
	for (EventHandler* e : eventHandlers) {
		e->handleEvent(ev);
	}
}

void GameState::addEventListener(EventHandler* evH) {
	eventHandlers.push_back(evH);
}

void GameState::addObject(GameObject* g) {
	gameObjects.push_back(g);
}

void GameState::runLater(DelayedCallback c) {
	c();
}

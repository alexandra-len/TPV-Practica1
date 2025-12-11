#include "gameState.h"
#include "game.h"
#include "gameobject.h"
#include <iostream>

GameState::GameState(Game* g) {
	game = g;
};

GameState::~GameState() {
	for (GameObject* g : gameObjects) {
		delete g;
	}
}

void GameState::render() const {
	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
		(*it)->render();
	}
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

GameState::Anchor GameState::addObject(GameObject* g) {
	gameObjects.push_back(g);
	return --gameObjects.end();
}

void GameState::runLater(DelayedCallback c) {
	delayedCallbacks.push_back(c);
}

void GameState::removeObject(GameState::Anchor a) {
	gameObjects.erase(a);
}

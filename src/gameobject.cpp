#include "gameobject.h"
#include "gameState.h"

GameObject::GameObject(GameState* gS) {
	gameS = gS;
};

GameObject::GameObject() {
	gameS = nullptr;
};

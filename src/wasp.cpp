#include "wasp.h"
#include <iostream>
using namespace std;

//Actualiza el estado de la avispa
void Wasp::update() {
	currentTime = SDL_GetTicks();
	if (currentTime >= deathTime) {
		lives = false;
		playState->deleteAfter(anchor);
	}
}

//Comprueba si la avispa sigue viva o no
bool Wasp::isAlive() const {
	return lives;
}

//Comprueba si la avispa colisiona con la rana o no
Collision Wasp::checkCollision(const SDL_FRect& otherRect) {
	Collision collision(Collision::NONE, { 0, 0 });

	// Caja de la avispa
	SDL_FRect waspRect(position.getX(), position.getY(), width, height);

	// Verificar colisión
	if (SDL_HasRectIntersectionFloat(&waspRect, &otherRect)) {
		collision.type = Collision::ENEMY;
	}
	return collision;
}

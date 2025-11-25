#include "wasp.h"
#include "collision.h"
#include "game.h"
#include <iostream>
using namespace std;

Wasp::Wasp(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s, int l)
	: SceneObject(g, t, p), speed(s), lifetime(l), deathTime(SDL_GetTicks() + lifetime), currentTime(0), lives(true) { }

void Wasp::setAnchor(PlayState::Anchor a) {
	anchor = a;
}

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

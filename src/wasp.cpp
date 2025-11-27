#include "wasp.h"
#include "collision.h"
#include "game.h"
#include <iostream>
using namespace std;

Wasp::Wasp(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s, int l)
	: SceneObject(g, t, p), speed(s), lifetime(l), deathTime(SDL_GetTicks() + lifetime), currentTime(0), lives(true) { }

void Wasp::setPlayAnchor(PlayState::Anchor a) {
	playAnchor = a;
}

void Wasp::setGameAnchor(GameState::Anchor a) {
	gameAnchor = a;
}

//Actualiza el estado de la avispa
void Wasp::update() {
	currentTime = SDL_GetTicks();
	if (currentTime >= deathTime) {
		lives = false;
		cout << "set destroy func" << endl;
		gameS->runLater([this]() {
			playState->removeObject(playAnchor);
			gameS->removeObject(gameAnchor);
			cout << "running destroy func" << endl;
		});
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

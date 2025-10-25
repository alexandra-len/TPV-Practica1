#include "wasp.h"

//Dibuja la avispa en pantalla
void Wasp::render() const {
	texture->render(SDL_FRect(position.getX(), position.getY(), width, height), 0, nullptr, SDL_FLIP_VERTICAL);
}

//Actualiza el estado de la avispa
void Wasp::update() {
	currentTime = SDL_GetTicks();
	if (currentTime >= deathTime) {
		lives = false;
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

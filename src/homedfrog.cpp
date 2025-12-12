#include "homedfrog.h"
#include "collision.h"
#include "playState.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>
using namespace std;
// Renderizado: Dibuja la rana solo si 'visible' es verdadero
void HomedFrog::render() const {
	if (visible) {
		SDL_FRect destRect = {
			position.getX(),
			position.getY(),
			(float)width,
			(float)height
		};
		// Renderiza el frame 0 de la textura
		texture->renderFrame(destRect, 0, 0);
	}
	// Código de Debug: para dibujar la caja de colisión
	//SDL_FRect collisionBox = getBoundingBox();
	//SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255); // Rojo
	//SDL_RenderRect(game->getRenderer(), &collisionBox);
}

bool HomedFrog::isHome() const {
	return visible;
}

void HomedFrog::setHome() {
	visible = true;
}

int HomedFrog::getX() const {
	return position.getX();
}

SDL_FRect HomedFrog::getBoundingBox() const
{
	const SDL_FRect destRect = { position.getX(),position.getY(),width, height };
	return destRect;
}

Collision HomedFrog::checkCollision(const SDL_FRect& otherRect) {
	Collision collision(Collision::NONE, { 0, 0 });

	SDL_FRect nestRect(position.getX(), position.getY(), width, height);
	// Verifica la intersección.
	if (SDL_HasRectIntersectionFloat(&nestRect, &otherRect)) {
		if (!visible) {
			// Si no está visible, significa que la nueva rana ha llegado a un nido vacío
			collision.type = Collision::HOME;
			visible = true;// Ocupa el nido
			playState->occupyNest();// Notifica al PlayState que un nido ha sido ocupado
		}
		else {
			// Si ya está visible, la nueva rana ha colisionado con una rana ya en casa
			collision.type = Collision::ENEMY;
		}
	}
	return collision;
}

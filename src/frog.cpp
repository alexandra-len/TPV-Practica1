#include "frog.h"
#include <iostream>
#include <SDL3_image/SDL_image.h>
using namespace std;

// Render de la rana
void Frog::render() const {
	if (texture != nullptr)
	{
		// Define el rectángulo donde se dibuja la rana
		SDL_FRect destRect = {
			position.getX(),
			position.getY(),
			(float)width,
			(float)height
		};

		// Dibuja la rana con orientación según su última dirección
		if (lastDirection == Point2D<int>(0, 1))
		{
			texture->renderFrame(destRect, 0, 0, SDL_FLIP_VERTICAL);
		}
		else if (lastDirection == Point2D<int>(0, -1))
		{
			texture->renderFrame(destRect, 0, 0, SDL_FLIP_NONE);
		}
		else if (lastDirection == Point2D<int>(-1, 0))
		{
			texture->renderFrame(destRect, 0, 0,-90, nullptr, SDL_FLIP_NONE);
		}
		else if (lastDirection == Point2D<int>(1, 0))
		{
			texture->renderFrame(destRect, 0, 0, 90, nullptr, SDL_FLIP_NONE);
		}
		else texture->renderFrame(destRect, 0, 0);

		SDL_FRect collisionBox = getBoundingBox();
		SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255); // Rojo
		SDL_RenderRect(game->getRenderer(), &collisionBox);
	}
}

// Devuelve el rectángulo de colision de la rana
SDL_FRect Frog::getBoundingBox() const
{
	// Ajusta el rectángulo para no usar todo el sprite
	const SDL_FRect destRect = { position.getX() + Game::FROG_COLLISION_MARGIN,position.getY() + Game::FROG_COLLISION_MARGIN, (float)width/2, (float)height/2};
	return destRect;
}

//Logica de la rana
void Frog::update() {
	// Calcula el desplazamiento
	Point2D<int> move = Point2D<int>(lastDirection.getX() * width, lastDirection.getY() * Game::TILE_SIZE);

	// Actualiza posición
	Point2D<int> newPos = position + move + Point2D<int>(round(velocity.getX()), velocity.getY());

	// Si saldrá de los bordes con el siguiente movimiento, no se mueve
	if (!(position.getX() < 0 || position.getX() +width > Game::WINDOW_WIDTH || position.getY() < 0 || position.getY() + height/2 > Game::WINDOW_HEIGHT)) {
		position = newPos;
	}
	// else do nothing

	Collision collision;
	collision = game->checkCollision(getBoundingBox());

	switch (collision.type) {
		// Si choca con un enemigo, pierde vida
		case Collision::ENEMY:
			hurt();
			break;
		// Si esta sobre un tronco, hereda su velocidad
		case Collision::PLATFORM:
			velocity = collision.speed;
			break;
		case Collision::HOME:
			position = initialPos;
			game->resetTimer();
			break;
		case Collision::NONE:
			velocity = Vector2D<float>(0, 0);
			// Si está en el área del río sin tronco debajo, muere
			if (position.getY() <= Game::RIVER_LOW) {
				hurt();
			}
			break;
	}
}

// Gestión de eventos del teclado
void Frog::handleEvent(const SDL_Event& event) {

	// Cambia la dirección en función de la tecla pulsada
	switch (event.key.key) {
	case SDLK_UP:
		lastDirection = Point2D<int>(0, -1);
		break;
	case SDLK_DOWN:
		lastDirection = Point2D<int>(0, 1);
		break;
	case SDLK_LEFT:
		lastDirection = Point2D<int>(-1, 0);
		break;
	case SDLK_RIGHT:
		lastDirection = Point2D<int>(1, 0);
		break;
	}
}

// Resta una vida a la rana y la reinicia en su posicion inicial
void Frog::hurt() {
	hp--;
	game->setHP(hp);
	position = initialPos;
	lastDirection = Point2D<int>(0, 0);

	// Si no quedan vidas, se termina el juego
	if (hp <= 0) {
		game->frogDeath();
	}
}

Collision Frog::checkCollision(const SDL_FRect& other) {
	return Collision{ Collision::NONE, {0,0} };
}

void Frog::loseLife() {
	hurt();
	game->resetTimer();
}

void Frog::onTimeout() {
	loseLife();
}

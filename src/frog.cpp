#include "frog.h"
#include "game.h"
#include "playState.h"
#include "collision.h"
#include <iostream>
#include <SDL3_image/SDL_image.h>
using namespace std;

Frog::Frog(GameState* g, Texture* t, Point2D<int> p) : SceneObject(g, t, p), initialPos(p), lastDirection(Point2D<int>(0, 0)), velocity(Vector2D<float>(0, 0)), hp(3) {}

Frog::Frog(GameState* g, std::istream& input) : SceneObject(g, g->getGame()->getTexture(Game::TextureName::FROG)), lastDirection(Point2D<int>(0, 0)) {
	// Lee las coordenadas de inicio desde un fichero
	int x, y, lives;
	if (!(input >> x >> y >> lives)) {
		throw FileFormatError(MAP_FILE);
	}

	initialPos = position = Point2D<int>(x, y);
	hp = lives;

	// Transmite al juego el numero de vidas totales que tiene.
	playState->setHP(hp);
}

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

		//SDL_FRect collisionBox = getBoundingBox();
		//SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255); // Rojo
		//SDL_RenderRect(game->getRenderer(), &collisionBox);
	}
}

// Devuelve el rectángulo de colision de la rana
SDL_FRect Frog::getBoundingBox() const
{
	// Ajusta el rectángulo para no usar todo el sprite
	const SDL_FRect destRect = { position.getX() + FROG_COLLISION_MARGIN,position.getY() + FROG_COLLISION_MARGIN, (float)width/2, (float)height/2};
	return destRect;
}

//Logica de la rana
void Frog::update() {
	// Calcula el desplazamiento
	Point2D<int> move = moveDirection * TILE_SIZE;

	// Actualiza posición
	Point2D<int> newPos = position + move + Point2D<int>(round(velocity.getX()), velocity.getY());

	// Si saldrá de los bordes con el siguiente movimiento, no se mueve
	if (!(newPos.getX() < 0 || newPos.getX() > Game::WINDOW_WIDTH - TILE_SIZE || newPos.getY() < 0 || newPos.getY() > Game::WINDOW_HEIGHT - TILE_SIZE*2)) {
		position = newPos;
	}
	moveDirection = Point2D<int>(0, 0);

	Collision collision;
	collision = playState->checkCollision(getBoundingBox());

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
			playState->resetTimer();
			break;
		case Collision::NONE:
			velocity = Vector2D<float>(0, 0);
			// Si está en el área del río sin tronco debajo, muere
			if (position.getY() <= PlayState::RIVER_LOW) {
				hurt();
			}
			break;
	}
}

// Gestión de eventos del teclado
void Frog::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		// Cambia la dirección en función de la tecla pulsada
		switch (event.key.key) {
		case SDLK_UP:
			lastDirection = moveDirection = Point2D<int>(0, -1);
			playState->playJumpSound();
			break;
		case SDLK_DOWN:
			lastDirection = moveDirection = Point2D<int>(0, 1);
			playState->playJumpSound();
			break;
		case SDLK_LEFT:
			lastDirection = moveDirection = Point2D<int>(-1, 0);
			playState->playJumpSound();
			break;
		case SDLK_RIGHT:
			lastDirection = moveDirection = Point2D<int>(1, 0);
			playState->playJumpSound();
			break;
		}
	}
}

// Resta una vida a la rana y la reinicia en su posicion inicial
void Frog::hurt() {
	hp--;
	playState->setHP(hp);
	position = initialPos;
	lastDirection = Point2D<int>(0, 0);

	// Si no quedan vidas, se termina el juego
	if (hp <= 0) {
		playState->frogDeath();
	}
	playState->resetTimer();
}

Collision Frog::checkCollision(const SDL_FRect& other) {
	return Collision{ Collision::NONE, {0,0} };
}

void Frog::onTimeEnd() {
	hurt();
}

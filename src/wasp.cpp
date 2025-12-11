#include "wasp.h"
#include "collision.h"
#include "game.h"
#include <iostream>
#include "FileFormatError.h"
#include <numbers>
using namespace std;

Wasp::Wasp(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s, int l, int n)
	: SceneObject(g, t, p), speed(s), lives(true), lifetime(l), deathTime(SDL_GetTicks() + lifetime), currentTime(0), nestNr(n) { }

Wasp::Wasp(GameState* g, std::istream& input)  : SceneObject(g, g->getGame()->getTexture(Game::WASP)), lives(true), currentTime(0) {
	int x, y, t;
	float vX, vY;
	if (!(input >> x >> y >> vX >> vY >> t)) {
		throw FileFormatError(MAP_FILE);
	}

	position = Point2D<int>{ x, y };
	speed = Vector2D<float>{ vX, vY };
	lifetime = t;
	deathTime = SDL_GetTicks() + lifetime;
	nestNr = -1;
}

void Wasp::setPlayAnchor(PlayState::Anchor a) {
	playAnchor = a;
}

void Wasp::setGameAnchor(GameState::Anchor a) {
	gameAnchor = a;
}

//Actualiza el estado de la avispa
void Wasp::update() {
	position = Point2D<int>(round(position.getX() + speed.getX()), round(position.getY() + speed.getY()));

	currentTime = SDL_GetTicks();
	if (currentTime >= deathTime) {
		destroyWasp();
	}
}

void Wasp::render() const {
	// El angulo se calcula: atan2(x, -y), porque atan2(y, x) da como resultado el angulo entre 
	// el segmento que pasa por el origen y el punto (x, y) y el eje X.
	// En este juego, la imagen original de la avispa mira hacia arriba por defecto (por lo tanto 0 grados
	// es mirar hacia arriba). Por esto, se cambian x e y en atan2(x, y), para rotar los ejes 90 grados 
	// (como si x es y e y es x). y se pone en negativo porque en SDL y positivo va hacia abajo.
	texture->render(getBoundingBox(), 360*atan2(speed.getX(), -speed.getY()) / (2 * numbers::pi));
}

void Wasp::destroyWasp() {
	lives = false;
	gameS->runLater([this]() {
		if (nestNr >= 0)
			playState->freeNest(nestNr);
		playState->removeObject(playAnchor);
		gameS->removeObject(gameAnchor);
		delete this;
	});
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

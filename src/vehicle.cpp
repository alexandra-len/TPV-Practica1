#include "vehicle.h"

void Vehicle::render() const {
	texture->render(SDL_FRect(position.getX(), position.getY()));
}

void Vehicle::update() {

}

//Collision Vehicle::checkCollision(const SDL_FRect& obj) {
//	return NULL;
//}
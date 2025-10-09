#include "vehicle.h"

void Vehicle::render() const {
	texture->render();
}

void Vehicle::update() {

}

//Collision Vehicle::checkCollision(const SDL_FRect& obj) {
//	return NULL;
//}
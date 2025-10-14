#include "wasp.h"

void Wasp::render() const {
	texture->render(SDL_FRect(position.getX(), position.getY(), width, height));
}

void Wasp::update() {

}

bool Wasp::isAlive() const {

}
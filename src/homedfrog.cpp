#include "homedfrog.h"

void HomedFrog::render() {
	texture->render(SDL_FRect(position.getX(), position.getY(), width, height));
}
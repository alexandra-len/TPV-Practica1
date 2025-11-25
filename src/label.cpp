#include "label.h"
#include "game.h"
#include "SDL3/SDL.h"

Label::Label(GameState* g, Texture* t, Point2D<int> p) : GameObject(g), texture(t), position(p) {};

void Label::render() const {
	SDL_FRect rect = SDL_FRect(position.getX(), position.getY(), texture->getFrameWidth(), texture->getFrameHeight());
	texture->render(rect);
}

void Label::update() {

}

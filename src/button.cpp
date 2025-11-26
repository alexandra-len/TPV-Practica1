#include "button.h"
#include "gameState.h"
#include "SDL3/SDL.h"

Button::Button(GameState* g, Texture* t, Point2D<int> p) : Label(g, t, p) {

}

Button::~Button() {

}

void Button::render() const {

}

void Button::connect(Callback c) {
	callbacks.push_back(c);
}

void Button::handleEvent(const SDL_Event&) {

}
void Button::setActive(bool active) {

}

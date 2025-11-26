#include "button.h"
#include "gameState.h"
#include "SDL3/SDL.h"
#include <iostream>
using namespace std;

Button::Button(GameState* g, Texture* t, Point2D<int> p) : Label(g, t, p) {
	hoverColor = { 128, 128, 128 };
	baseColor = { 255, 255, 255 };
}

Button::~Button() {

}

void Button::render() const {
	if (active) {
		SDL_FRect rect = SDL_FRect(position.getX(), position.getY(), texture->getFrameWidth(), texture->getFrameHeight());
		if (hovering) {
			texture->render(rect, hoverColor);
		}
		else {
			texture->render(rect, baseColor);
		}
	}
}

void Button::connect(Callback c) {
	callback = c;
}

void Button::handleEvent(const SDL_Event& ev) {
	if (active) {
		if (ev.type == SDL_EVENT_MOUSE_MOTION) {
			SDL_FPoint clickPos = { ev.button.x, ev.button.x };
			SDL_FRect clickRect = SDL_FRect(position.getX(), position.getY(), width, height);
			hovering = SDL_PointInRectFloat(&clickPos, &clickRect);
		}
		else if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN && hovering) {
			callback();
			cout << "click" << endl;
		}
	}
}
void Button::setActive(bool active) {

}

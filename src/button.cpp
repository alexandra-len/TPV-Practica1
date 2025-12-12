#include "button.h"
#include "gameState.h"
#include "SDL3/SDL.h"
#include <iostream>
using namespace std;

// Constructor: Inicializa colores, el estado de hover/activo y se registra como oyente de eventos
Button::Button(GameState* g, Texture* t, Point2D<int> p) : Label(g, t, p), hovering(false), active(true) {
	hoverColor = { 255, 255, 0 };
	baseColor = { 255, 255, 255 };

	gameS->addEventListener(this);
}

Button::~Button() {

}
// Renderizado: Dibuja el botón solo si está activo
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

// Asigna la función de callback que se ejecutará al hacer clic
void Button::connect(Callback c) {
	callback = c;
}

void Button::handleEvent(const SDL_Event& ev) {
	if (active) {
		if (ev.type == SDL_EVENT_MOUSE_MOTION) {
			SDL_FPoint clickPos = { ev.button.x, ev.button.y };
			SDL_FRect clickRect = SDL_FRect(position.getX(), position.getY(), texture->getFrameWidth(), texture->getFrameHeight());
			hovering = SDL_PointInRectFloat(&clickPos, &clickRect);
		}
		else if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN && hovering) {
			callback();
		}
	}
}
// Establece el estado activo/inactivo del botón
void Button::setActive(bool a) {
	active = a;
}

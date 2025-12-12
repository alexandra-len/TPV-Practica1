#pragma once
#include "label.h"
#include "eventHandler.h"
#include <vector>
#include <functional>

// Clase Button: Es un Label interactivo que puede manejar eventos
class Button : public Label, public EventHandler
{
	// Tipo para la función de callback (función sin parámetros ni retorno)
	using Callback = std::function<void()>;

	Callback callback;// La función a ejecutar cuando se hace clic
	bool hovering;// Verdadero si el ratón está sobre el botón
	bool active;// Verdadero si el botón está interactuable y visible

	SDL_Color hoverColor, baseColor;// Colores para el estado normal y al pasar el ratón

public:
	Button(GameState* g, Texture* t, Point2D<int> p);
	~Button();

	void render() const override;

	void connect(Callback c);// Asigna la función de callback al botón
	void handleEvent(const SDL_Event&) override;
	void setActive(bool active);// Establece si el botón está activo o no
};


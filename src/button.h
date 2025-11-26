#pragma once
#include "label.h"
#include "eventHandler.h"
#include <vector>
#include <functional>

class Button : public Label, public EventHandler
{
	using Callback = std::function<void()>;

	Callback callback;
	bool hovering;
	bool active;

	SDL_Color hoverColor, baseColor;

public:
	Button(GameState* g, Texture* t, Point2D<int> p);
	~Button();

	void render() const override;

	void connect(Callback c);
	void handleEvent(const SDL_Event&) override;
	void setActive(bool active);
};


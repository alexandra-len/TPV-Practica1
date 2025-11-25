#pragma once
#include "label.h"
#include "eventHandler.h"
#include <vector>
#include <functional>

class Button : public Label, public EventHandler
{
	using Callback = std::function<void()>;

	std::vector<Callback> callbacks;
	bool hovering;
	bool active;

public:
	Button(GameState* g, Texture* t, Point2D<int> p) : Label(g, t, p) {};
	~Button() = default;

	void render() const override;

	void connect(Callback c) {
		callbacks.push_back(c);
	}
	void handleEvent(const SDL_Event&) override;
	void setActive(bool active);
};


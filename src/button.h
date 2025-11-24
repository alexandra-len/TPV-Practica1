#pragma once
#include "label.h"
#include <vector>

class Button : public Label, public EventHandler
{
	using Callback = std::function<void()>;

	std::vector<Callback> callbacks;

public:
	Button(GameState* g, Texture* t, Point2D<int> p) : Label(g, t, p) {};

	void connect(Callback c) {
		callbacks.push_back(c);
	}
};


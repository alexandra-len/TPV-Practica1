#pragma once
#include "game.h"
#include "frog.h"

class InfoBar : public GameObject
{
	int frogHP;

	Texture* frogImg;

	int width;
	int height;

public:
	InfoBar(Game* g, Texture* t) : GameObject(g), frogImg(t) {
		frogHP = g->getHP();
		width = frogImg->getFrameWidth();
		height = frogImg->getFrameHeight();
	}

	void render() const override;
	void update() override;
};


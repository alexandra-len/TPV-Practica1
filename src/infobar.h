#pragma once
#include "game.h"
#include "frog.h"

class InfoBar
{
	int remainingHP;

	int totalNests;
	int occupiedNests;

	Frog* frog;
	Texture* frogImg;

	int width;
	int height;

public:
	InfoBar(Frog* f, int nests, Texture* t) : frog(f), frogImg(t), totalNests(nests), occupiedNests(0) {
		remainingHP = frog->getHP();
		width = frogImg->getFrameWidth();
		height = frogImg->getFrameHeight();
	}

	void render();
	void update();
};


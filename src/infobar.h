#pragma once
#include "game.h"
#include "frog.h"

class InfoBar : public GameObject
{
	int frogHP;

	Texture* frogImg;

	int frogWidth, frogHeight;
	int timerPosX, timerPosY;
	int timerWidth, timerHeight;

	SDL_FRect timerOutline;

public:
	InfoBar(GameState* g, Texture* t) : GameObject(g), frogImg(t) {
		frogHP = g->getHP();
		frogWidth = frogImg->getFrameWidth();
		frogHeight = frogImg->getFrameHeight();
		timerHeight = frogHeight;
		timerWidth = Game::WINDOW_WIDTH / 3;

		timerPosX = 2 * Game::WINDOW_WIDTH / 3 - 10;
		timerPosY = Game::WINDOW_HEIGHT - Game::LOW_MARGIN;
		
		timerOutline = {
			(float)timerPosX,
			(float)timerPosY,
			(float)timerWidth,
			(float)timerHeight/4
		};
	}

	void render() const override;
	void update() override;

private:
	void renderTimer() const;
};


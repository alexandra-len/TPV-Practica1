#pragma once
#include "vector2D.h"
#include "gameobject.h"

class InfoBar : public GameObject
{
	static constexpr int DISTANCE_FROM_BELOW = 36;

	int frogHP;
	float remainingTime;

	Texture* frogImg;

	Point2D<int> position;

	int frogWidth, frogHeight;
	int timerPosX, timerPosY;
	int timerWidth, timerHeight;

	SDL_FRect timerOutline;

public:
	InfoBar(GameState* g, Texture* t, Point2D<int> p) : GameObject(g), frogImg(t), position(p), frogHP(0) {
		frogWidth = frogImg->getFrameWidth();
		frogHeight = frogImg->getFrameHeight();
		
		timerHeight = frogHeight;
		timerWidth = Game::WINDOW_WIDTH / 3;

		timerPosX = 2 * Game::WINDOW_WIDTH / 3 - 10;
		timerPosY = Game::WINDOW_HEIGHT - DISTANCE_FROM_BELOW;
		
		timerOutline = {
			(float)timerPosX,
			(float)timerPosY,
			(float)timerWidth,
			(float)timerHeight/4
		};
	}

	void render() const override;
	void update() override {}
	void setHP(int hp) {
		frogHP = hp;
	}
	void setTime(float time) {
		remainingTime = time;
	}

private:
	void renderTimer() const;
};


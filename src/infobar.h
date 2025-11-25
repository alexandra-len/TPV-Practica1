#pragma once
#include "vector2D.h"
#include "gameobject.h"
#include "SDL3/SDL.h"

class Texture;

class InfoBar : public GameObject
{
	static constexpr int DISTANCE_FROM_BELOW = 36;

	int frogHP;
	float remainingTime;

	Texture* frogImg;

	int frogWidth, frogHeight;
	int timerPosX, timerPosY;
	int timerWidth, timerHeight;

	SDL_FRect timerOutline;

public:
	InfoBar(GameState* g, Texture* t);

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


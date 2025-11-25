#include "crosser.h"
#include "game.h"
#include "playState.h"

void Crosser::update() {
	int rightLimit = Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN - (width - backjump);
	int leftLimit = -(Game::WINDOW_WIDTH_MARGIN + backjump);

	if (speed.getX() > 0 && position.getX() > rightLimit)
	{
		position = Point2D<int>(backjump == 0 ? -width : -Game::WINDOW_WIDTH_MARGIN, position.getY());
	}

	else if (speed.getX() < 0 && position.getX() < leftLimit)
	{
		position = Point2D<int>(backjump == 0 ? Game::WINDOW_WIDTH : Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN - width, position.getY());
	}

	else {
		position = Point2D<int>(round(position.getX() + speed.getX()), position.getY());
	}
}

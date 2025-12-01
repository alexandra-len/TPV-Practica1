#include "turtlegroup.h"
#include "playState.h"
#include "collision.h"
#include "game.h"

TurtleGroup::TurtleGroup(GameState* g, std::istream& input) : Platform(g), frame(0) {
	int x, y, sink;
	float s;
	if (!(input >> x >> y >> s >> numTurtles >> sink)) {
		throw FileFormatError(MAP_FILE);
	}

	position = Point2D<int>(x, y);
	speed = Vector2D<float>(s / Game::FRAME_RATE, 0);

	sinks = sink == 1;

	texture = gameS->getGame()->getTexture(Game::TURTLES);
	width = texture->getFrameWidth() * numTurtles;
	height = texture->getFrameHeight();

	backjump = texture->getFrameWidth();
};

void TurtleGroup::render() const {
	if (texture != nullptr) {
		for (int i = 0; i < numTurtles; i++) {
			SDL_FRect rect = {
				position.getX() + i * width/numTurtles,
				position.getY(),
				width/numTurtles,
				height
			};

			if (sinks) {
				texture->renderFrame(rect, 0, frame);
			}
			else {
				texture->renderFrame(rect, 0, frame);
			}
		}
	}
}

void TurtleGroup::update() {
	if (sinks) {
		frame = (SDL_GetTicks() / TURTLE_SINK_RATE) % TURTLE_SINK_FRAMES;
	}
	
	int rightLimit = Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN;
	int leftLimit = -Game::WINDOW_WIDTH_MARGIN - width;

	if (speed.getX() > 0 && position.getX() > rightLimit)
	{
		position = Point2D<int>(-Game::WINDOW_WIDTH_MARGIN, position.getY());
	}

	else if (speed.getX() < 0 && position.getX() < leftLimit)
	{
		position = Point2D<int>(Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN - width, position.getY());
	}

	else {
		position = Point2D<int>(round(position.getX() + speed.getX()), position.getY());
	}
}

SDL_FRect TurtleGroup::getBoundingBox() const {
	if (texture != nullptr && (frame <= 5 || !sinks)) {
		SDL_FRect rect = {
			position.getX(),
			position.getY(),
			width,
			height
		};
		return rect;
	}
	else return SDL_FRect{ 0, 0, 0, 0 };
}

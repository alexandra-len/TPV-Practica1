#include "crosser.h"
#include "game.h"
#include "playState.h"

Crosser::Crosser(GameState* g) : SceneObject(g) {};

Crosser::Crosser(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s, int bj) : SceneObject(g, t, p), speed(s) {
	// La velocidad ajustada al frame rate
	speed = Vector2D<float>(s.getX() / Game::FRAME_RATE, s.getY() / Game::FRAME_RATE);
}

Crosser::Crosser(GameState* g, std::istream& input, int textureNrOffset, int bj = -1) : SceneObject(g) {
	int textureNr, x, y;
	float s;
	if (!(input >> x >> y >> s >> textureNr)) {
		throw FileFormatError("");
	}

	position = Point2D<int>(x, y);
	speed = Vector2D<float>(s / Game::FRAME_RATE, 0);

	int finalTextureIndex = textureNrOffset + textureNr;

	if (finalTextureIndex < 0 || finalTextureIndex >= Game::NUM_TEXTURES) {
		throw FileFormatError(MAP_FILE);
	}

	texture = gameS->getGame()->getTexture((Game::TextureName)(finalTextureIndex));
	width = texture->getFrameWidth();
	height = texture->getFrameHeight();

	if (bj == -1) {
		backjump = texture->getFrameWidth();
	}
	else {
		backjump = bj;
	}
}

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

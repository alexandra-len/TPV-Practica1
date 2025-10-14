#include "game.h"
#include "texture.h"
#include "vector2D.h"

class HomedFrog
{
	Game* game;
	Texture* texture;
	Point2D<int> position;
	int width;
	int height;

public:
	HomedFrog(Game* g, Texture* t, Point2D<int> p) : game(g), texture(t), position(p) {
		width = texture->getFrameWidth();
		height = texture->getFrameHeight();
	};

	void render();
};
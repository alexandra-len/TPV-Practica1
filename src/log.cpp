#include "log.h"

Log::Log(GameState* g, Texture* t, Point2D<int> p, Vector2D<float> s) : Platform(g, t, p, s, t->getFrameWidth()) {};

Log::Log(GameState* g, std::istream& input) : Platform(g, input, LOG1_TEXTURE_NR, -1) {};

#include "turtlegroup.h"
#include "playState.h"
#include "collision.h"
#include "game.h"

//Lee los datos del grupo de tortugas desde un stream
TurtleGroup::TurtleGroup(GameState* g, std::istream& input) : Platform(g), frame(0) {
	int x, y, sink;
	float s;
	if (!(input >> x >> y >> s >> numTurtles >> sink)) {
		throw FileFormatError(MAP_FILE);
	}

	position = Point2D<int>(x, y);
	speed = Vector2D<float>(s / Game::FRAME_RATE, 0);

	sinks = sink == 1;

	// Establece la textura y calcula dimensiones
	texture = gameS->getGame()->getTexture(Game::TURTLES);
	width = texture->getFrameWidth() * numTurtles;
	height = texture->getFrameHeight();

	backjump = texture->getFrameWidth();
};

// Dibuja cada tortuga del grupo
void TurtleGroup::render() const {
	if (texture != nullptr) {
		for (int i = 0; i < numTurtles; i++) {
			// Define el rectángulo de destino para cada tortuga
			SDL_FRect rect = {
				position.getX() + i * width/numTurtles,
				position.getY(),
				width/numTurtles,// Ancho de una sola tortuga
				height
			};
			// Dibuja el frame de animación actual
			texture->renderFrame(rect, 0, frame);
		}
	}
}
// Actualiza el movimiento cíclico y la animación de hundimiento
void TurtleGroup::update() {
	// Calcula el frame de animación
	if (sinks) {
		// Cicla entre los frames de hundimiento
		frame = (SDL_GetTicks() / TURTLE_SINK_RATE) % TURTLE_SINK_FRAMES;
	}
	else {
		// Cicla entre los frames estáticos
		frame = (SDL_GetTicks() / TURTLE_SINK_RATE) % TURTLE_STATIC_FRAMES;
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
	// Si no ha salido de los límites, aplica el movimiento normal
	else {
		position = Point2D<int>(round(position.getX() + speed.getX()), position.getY());
	}
}
// Devuelve la caja de colisión
SDL_FRect TurtleGroup::getBoundingBox() const {
	//solo si hay textura Y el grupo no se está hundiendo (frame <= 5).
	// Si el frame es > 5, se devuelve una caja vacía, impidiendo la colisión
	if (texture != nullptr && (frame <= 5 || !sinks)) {
		SDL_FRect rect = {
			position.getX(),
			position.getY(),
			width,
			height
		};
		return rect;
	}
	else return SDL_FRect{ 0, 0, 0, 0 };// Caja de colisión nula (rana cae al agua)
}

#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include "vehicle.h"
#include "log.h"

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "../assets/maps/default.txt";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;

};

constexpr const char* const imgBase = "../assets/images/";

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"frog.png", 1, 2},
	{"background.png"},
	{"car1.png"},
	{"car2.png"},
	{"car3.png"},
	{"car4.png"},
	{"car5.png"},
	{"log1.png"},
	{"log2.png"},
	{"wasp.png"}

};

Game::Game()
  : exit(false)
{
	// Carga SDL y sus bibliotecas auxiliares
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(WINDOW_TITLE,
	                          WINDOW_WIDTH,
	                          WINDOW_HEIGHT,
	                          0);

	if (window == nullptr)
		throw "window: "s + SDL_GetError();

	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr)
		throw "renderer: "s + SDL_GetError();

	// Carga las texturas al inicio
	for (size_t i = 0; i < textures.size(); i++) {
		auto [name, nrows, ncols] = textureList[i];
		textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
	}

	randomGenerator = std::mt19937(std::time(nullptr));

	logs.push_back(new Log(this, getTexture(TextureName::LOG1), Point2D<int>(50, 100), Vector2D<float>(72.6, 0.0f)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG2), Point2D<int>(200, 150), Vector2D<float>(96, 0.0f)));

	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE1), Point2D<int>(50, 372), Vector2D<float>(-48, 0.0)));


	// Render la primera vez.
	render();

	
	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

}

Game::~Game()
{
	for (size_t i = 0; i < textures.size(); i++) {
		delete textures[i];
	}
	for (int i = 0; i < logs.size(); i++) {
		delete logs[i];
	}
	for (int i = 0; i < vehicles.size(); i++) {
		delete vehicles[i];
	}
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	getTexture(TextureName::BACKGROUND)->render();
	// TODO

	for (int i = 0; i < logs.size(); i++) {
		logs[i]->render();
	}
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->render();
	}

	SDL_RenderPresent(renderer);

}

void
Game::update()
{
	for (int i = 0; i < logs.size(); i++) {
		logs[i]->update();
	}
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->update();
	}
}

void
Game::run()
{
	while (!exit) {
		// TODO: implementar bucle del juego
		update();
		render();
	}
}

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		// TODO
	}
}

bool
Game::checkCollision(const SDL_FRect& rect) const
{
	// TODO: cambiar el tipo de retorno a Collision e implementar
	return false;
}

int Game::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<int>(min, max)(randomGenerator);
}

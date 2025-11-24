#include "game.h"

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <format>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include "vehicle.h"
#include "log.h"
#include "wasp.h"
#include "frog.h"
#include "homedfrog.h"
#include "infobar.h"
#include "turtlegroup.h"

#include "SDLError.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"

using namespace std;

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;

};

// Ruta base para las imagenes
constexpr const char* const imgBase = "../assets/images/";

constexpr const char* const MAP_FILE = "../assets/maps/turtles.txt";
constexpr const char* const JUMP_FILE = "../assets/sounds/jump.wav";

// Lista de texturas a cargar
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
	{"wasp.png"},
	{"turtle.png", 1, 7}
};

Game::Game()
  : exit(false)
{
	// Carga SDL y sus bibliotecas auxiliares
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window = SDL_CreateWindow(WINDOW_TITLE,
	                          WINDOW_WIDTH,
	                          WINDOW_HEIGHT,
	                          0);

	if (window == nullptr)
		throw SDLError();

	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr)
		throw SDLError();

	// Carga las texturas al inicio
	for (size_t i = 0; i < textures.size(); i++) {
		auto [name, nrows, ncols] = textureList[i];
		if (!(filesystem::exists(string(imgBase) + name))) {
			throw FileNotFoundError(MAP_FILE);
		}
		textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
	}
}

Game::~Game()
{
	// Libera la memoria de todos los objetos creados
	/*delete infoBar;

	for (auto& obj : objects) {
		delete obj;
	}*/

	for (size_t i = 0; i < textures.size(); i++) {
		delete textures[i];
	}
	/*if (jumpStream) {
		SDL_DestroyAudioStream(jumpStream);
		jumpStream = nullptr;
	}
	if (jumpData) {
		SDL_free(jumpData);
		jumpData = nullptr;
	}*/
}

void
Game::run()
{
	uint64_t startTime, frameTime;
	while (!exit && !empty()) {
		// Tiempo al inicio del frame
		startTime = SDL_GetTicks();

		update();
		render();
		
		// Tiempo que tomo el frame
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE) {
			SDL_Delay(FRAME_RATE - frameTime);
		}
	}
}

#include "game.h"

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include "vehicle.h"
#include "log.h"
#include "wasp.h"
#include "frog.h"
#include "homedfrog.h"
#include "infobar.h"

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

// Ruta base para las imagenes
constexpr const char* const imgBase = "../assets/images/";

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
		if (!(filesystem::exists(string(imgBase) + name))) {
			throw string("Image file invalid or does not exist.");
		}
		textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
	}

	// Inicializa el generador de números aleatorios con la hora actual
	randomGenerator = std::mt19937(std::time(nullptr));

	// Cargar el mapa
	try {
		loadMap();
	}
	catch (string& e) {
		for (auto t : textures) {
			delete t;
		}
		throw e;

	}

	// Crea los nidos
	for (int i = 0; i < NEST_NR; i++) {
		nests.push_back(new HomedFrog(this, getTexture(TextureName::FROG), Point2D<int>(NEST_FROG_STARTING_X + NEST_FROG_DISTANCE_X * i, NEST_FROG_Y)));
	}

	// Inicializa el info bar
	infoBar = new InfoBar(player, NEST_NR, getTexture(TextureName::FROG));
	
	// Inicializa el tiempo para la aparición de la primera avispa
	timeUntilWasp = getRandomRange(WASP_MIN_DELAY, SDL_GetTicks() + WASP_MIN_DELAY);
	waspDestructionTime = SDL_GetTicks() + timeUntilWasp;

	// Render la primera vez.
	render();

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Game::~Game()
{
	// Libera la memoria de todos los objetos creados
	for (int i = 0; i < logs.size(); i++) {
		delete logs[i];
	}
	for (int i = 0; i < vehicles.size(); i++) {
		delete vehicles[i];
	}
	for (int i = 0; i < nests.size(); i++) {
		delete nests[i];
	}
	for (int i = 0; i < wasps.size(); i++) {
		delete wasps[i];
	}
	delete infoBar;
	delete player;
	for (size_t i = 0; i < textures.size(); i++) {
		delete textures[i];
	}
}

void
Game::render() const
{
	// Limpia la pantalla
	SDL_RenderClear(renderer);

	// Renderiza el fondo
	getTexture(TextureName::BACKGROUND)->render();

	// Renderiza los troncos
	for (int i = 0; i < logs.size(); i++) {
		logs[i]->render();
	}
	// Renderiza los vehículos
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->render();
	}
	// Renderiza las avispas
	for (const auto& w : wasps) {
		w->render();
	}
	// Renderiza los nidos si están ocupados
	for (const auto& hFrog : nests) {
		if (hFrog->isHome()) {
			hFrog->render();
		}
	}
	player->render();
	infoBar->render();

	SDL_RenderPresent(renderer);

}

void
Game::update()
{
	player->update();
	infoBar->update();
	for (int i = 0; i < logs.size(); i++) {
		logs[i]->update();
	}
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->update();
	}

	// Obtiene el tiempo actual
	currentTime = SDL_GetTicks();

	// Genera una avispa
	if (currentTime >= waspDestructionTime) {
		int nestNr;
		// Elige un nido aleatorio que no esté ocupado
		do {
			nestNr = getRandomRange(0, waspPositions.size() - 1);
		} while (nests[nestNr]->isHome());

		// Crea una avispa en la posición del nido elegido, con vida aleatoria
		wasps.push_back(new Wasp(this, getTexture(TextureName::WASP), Point2D<int>(waspPositions[nestNr].getX(), NEST_ROW_Y), Vector2D<float>(0, 0), getRandomRange(WASP_MIN_DELAY, WASP_MAX_DELAY)));
		
		// Programa la próxima avispa
		timeUntilWasp = getRandomRange(WASP_MIN_DELAY, SDL_GetTicks() + WASP_MIN_DELAY);
		waspDestructionTime = currentTime + timeUntilWasp;
	}

	// Actualiza las avispas y elimina las muertas
	for (int i = 0; i < wasps.size(); i++) {
		wasps[i]->update();
		if (!wasps[i]->isAlive()) {
			delete wasps[i];
			wasps.erase(wasps.begin() + i);
		}
	}
}

void
Game::run()
{
	uint64_t startTime, frameTime;
	while (!exit) {
		// Tiempo al inicio del frame
		startTime = SDL_GetTicks();
		cout << "TICK" << endl;
		exit = checkVictory();
		handleEvents();
		update();
		render();
		// Tiempo que tomo el frame
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE) {
			SDL_Delay(FRAME_RATE - frameTime);
		}
	}
	cout << "Game ended";
}

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			exit = true;
		}
		else if (event.type == SDL_EVENT_KEY_DOWN) {
			// Pasa el evento a la rana
			player->handleEvent(event);
		}
	}
}

Collision
Game::checkCollision(const SDL_FRect& rect) const
{
	Collision col{ Collision::NONE, {0,0} };

	// Verifica colisiones con troncos
	for (const auto& l : logs) {
		col = l->checkCollision(rect);
		if (col.type != Collision::NONE)
			return col;
	}
	if (col.type != Collision::NONE)
		return col;
	// Verifica colisiones con vehículos
	for (const auto& v : vehicles) {
		col = v->checkCollision(rect);
		if (col.type != Collision::NONE)
			break;
	}
	if (col.type != Collision::NONE) 
		return col;
	// Verifica colisiones con avispas
	for (const auto& w : wasps) {
		col = w->checkCollision(rect);
		if (col.type != Collision::NONE)
			return col;
	}
	if (col.type != Collision::NONE) 
		return col;
	
	// Verifica colisiones con nidos
	for (const auto& n : nests) {
		col = n->checkCollision(rect);
		if (col.type != Collision::NONE) {
			handleNestCollision(col, n);
			return col;
		}
	}
	return col;
}

// Maneja la colisión con un nido
void Game::handleNestCollision(Collision col, HomedFrog* f) const {
	// Marca el nido como ocupado
	if (col.type == Collision::HOME) {
		f->setHome();
	}
}

void Game::exitGame() {
	exit = true;
}

// Genera un número aleatorio
int Game::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<int>(min, max)(randomGenerator);
}

// Carga el mapa desde un archivo
void Game::loadMap() {
	ifstream map;
	map.open(MAP_FILE);

	if (!map) {
		throw string("Map file not found");
	}

	string c;
	while (map >> c) {
		if (c == "#") {
			map.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			// Carga vehículos, troncos y la rana según las etiquetas
			if (c == "V") {
				vehicles.push_back(new Vehicle(this, map));
			}
			else if (c == "L") {
				//logs.push_back(new Log(this, map));
			}
			else if (c == "F") {
				player = new Frog(this, map);
			}
		}
	}

}

// TODO: check victory through variable of nests occupied
bool Game::checkVictory() {
	int i = 0;
	bool nestsFull = true;
	while (i < nests.size() && nestsFull) {
		nestsFull = nests[i]->isHome();
	}
	return nestsFull;
}

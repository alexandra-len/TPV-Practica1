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

#include "SDLError.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"

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

	const char* jumpPath = "../assets/sounds/jump.wav";

	if (!SDL_LoadWAV(jumpPath, &jumpSpec, &jumpData, &jumpDataLen)) {
		throw SDLError();
	}

	jumpStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &jumpSpec, nullptr, nullptr);
	if (!jumpStream) {
		SDL_free(jumpData);
		throw SDLError();
	}
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
	nestsOccupied = 0;

	// Inicializa el info bar
	infoBar = new InfoBar(this, getTexture(TextureName::FROG));

	remainingSeconds = timeLimitSeconds;
	lastSecondTick = SDL_GetTicks();
	
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
	delete infoBar;

	for (auto& obj : objects) {
		delete obj;
	}

	for (auto& n : nests) {
		delete n;
	}

	for (size_t i = 0; i < textures.size(); i++) {
		delete textures[i];
	}
	if (jumpStream) {
		SDL_DestroyAudioStream(jumpStream);
		jumpStream = nullptr;
	}
	if (jumpData) {
		SDL_free(jumpData);
		jumpData = nullptr;
	}
}

void
Game::render() const
{
	// Limpia la pantalla
	SDL_RenderClear(renderer);

	// Renderiza el fondo
	getTexture(TextureName::BACKGROUND)->render();

	for (auto* obj : objects) {
		obj->render();
	}

	for (auto* n : nests) {
		n->render();
	}

	infoBar->render();

	SDL_RenderPresent(renderer);

}

void
Game::update()
{
	for (auto& obj : objects) {
		obj->update();
	}

	infoBar->update();

	Uint32 now = SDL_GetTicks();
	if (now - lastSecondTick >= 1000) {

		int secsPassed = (now - lastSecondTick) / 1000;
		remainingSeconds -= secsPassed;
		lastSecondTick += secsPassed * 1000;

		if (remainingSeconds <= 0) {
			player->onTimeout();
			resetTimer();
		}

		std::cout << "Tiempo restante: " << remainingSeconds << std::endl;
	}
	// Obtiene el tiempo actual
	currentTime = SDL_GetTicks();

	// Genera una avispa
	if (currentTime >= waspDestructionTime) {
		int nestNr;
		// Elige un nido aleatorio que no esté ocupado
		do {
			nestNr = getRandomRange(0, NEST_NR - 1);
		} while (dynamic_cast<HomedFrog*>(nests[nestNr])->isHome());

		// Crea una avispa en la posición del nido elegido, con vida aleatoria
		Wasp* newWasp = new Wasp(this, getTexture(TextureName::WASP), Point2D<int>(waspPositions[nestNr].getX(), NEST_ROW_Y), Vector2D<float>(0, 0), getRandomRange(WASP_MIN_DELAY, WASP_MAX_DELAY));
		objects.push_back(newWasp);
		newWasp->setAnchor(--objects.end());
		
		// Programa la próxima avispa
		timeUntilWasp = getRandomRange(WASP_MIN_DELAY, SDL_GetTicks() + WASP_MIN_DELAY);
		waspDestructionTime = currentTime + timeUntilWasp;
	}
}

void
Game::run()
{
	uint64_t startTime, frameTime;
	while (!exit) {
		// Tiempo al inicio del frame
		startTime = SDL_GetTicks();
		exit = checkVictory();
		handleEvents();
		update();
		render();
		deleteObjects();
		// Tiempo que tomo el frame
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE) {
			SDL_Delay(FRAME_RATE - frameTime);
		}
	}
	cout << "Game ended" << endl;
	if (nestsFull) {
		cout << "You won!";
	}
	else if (deadFrog) {
		cout << "You lost!";
	}
	else {
		cout << "You closed the game.";
	}
	cout << endl;
}

void Game::deleteObjects() {
	for (Anchor& obj : objToDelete) {
		delete* obj;
		objects.erase(obj);
	}

	objToDelete = std::vector<Anchor>();
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
			if (event.key.key == SDLK_0) {
				const SDL_MessageBoxButtonData buttons[] = {
					{SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancelar"},
					{0, 1, "Reiniciar"},
				};
				SDL_MessageBoxData boxData = { SDL_MESSAGEBOX_INFORMATION,window,"Reinicar juego","Quieres reiniciar el juego?",2,buttons
				};
				int button;
				SDL_ShowMessageBox(&boxData, &button);
				if (button == 1) {
					restartGame();
				}
			}
			else {
				dynamic_cast<Frog*>(player)->handleEvent(event);
			}
		}
	}
}

Collision
Game::checkCollision(const SDL_FRect& rect) const
{
	Collision col{ Collision::NONE, {0,0} };

	for (const auto& obj : objects) {
		col = obj->checkCollision(rect);
		if (col.type != Collision::NONE)
			return col;
	}
	if (col.type != Collision::NONE)
		return col;

	for (auto& n : nests) {
		col = n->checkCollision(rect);
		if (col.type != Collision::NONE)
			return col;
	}

	return col;
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
		throw FileNotFoundError(MAP_FILE);
	}

	int lineCounter = 1;

	try {
		string c;
		while (map >> c) {
			if (!map) {
				throw FileFormatError(MAP_FILE, lineCounter);
			}
			if (c == "#") {
				map.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else {
				// Carga vehículos, troncos y la rana según las etiquetas
				if (c == "V") {
					objects.push_back(new Vehicle(this, map));
				}
				else if (c == "L") {
					objects.push_back(new Log(this, map));
				}
				else if (c == "F") {
					player = new Frog(this, map);
					objects.push_back(player);
				}
			}
			lineCounter++;
		}
	}
	catch (...) {
		for (auto* obj : objects) {
			delete obj;
		}
		for (size_t i = 0; i < textures.size(); i++) {
			delete textures[i];
		}
		throw FileFormatError(MAP_FILE, lineCounter);
	}

}

bool Game::checkVictory() {
	if (nestsOccupied == NEST_NR) {
		nestsFull = true;
	}
	return deadFrog || nestsFull;
}

void Game::resetTimer() {
	remainingSeconds = timeLimitSeconds;
	lastSecondTick = SDL_GetTicks();
	std::cout << "[Timer] reset to " << remainingSeconds << std::endl;

	// if (infoBar) infoBar->setTimeRemaining(remainingSeconds);
}

void Game::playJumpSound() {
	if (!jumpStream || !jumpData) return;

	if (!SDL_PutAudioStreamData(jumpStream, jumpData, static_cast<int>(jumpDataLen))) {
		SDL_Log("SDL_PutAudioStreamData failed:", SDL_GetError());
		return;
	}

	SDL_ResumeAudioStreamDevice(jumpStream);
}

void Game::restartGame()
{
	for (auto* obj : objects) {
		delete obj;
	}objects.clear();

	for (auto* n : nests) {
		delete n;
	}
	nests.clear();
	nestsOccupied = 0;

	delete infoBar;

	for (int i = 0; i < NEST_NR; i++) {
		nests.push_back(new HomedFrog(this,getTexture(TextureName::FROG),Point2D<int>(NEST_FROG_STARTING_X + NEST_FROG_DISTANCE_X * i,NEST_FROG_Y)));
	}

	timeUntilWasp = getRandomRange(WASP_MIN_DELAY, SDL_GetTicks() + WASP_MIN_DELAY);
	waspDestructionTime = SDL_GetTicks() + timeUntilWasp;

	infoBar = new InfoBar(this, getTexture(TextureName::FROG));

	loadMap();
}


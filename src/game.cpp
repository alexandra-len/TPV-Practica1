#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include "vehicle.h"
#include "log.h"
#include "wasp.h"
#include "frog.h"
#include "homedfrog.h"

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

	player = new Frog(this, getTexture(TextureName::FROG), Point2D<int>(205, 402));

	nests.push_back(new HomedFrog(this, getTexture(TextureName::FROG), Point2D<int>(20, 23)));
	nests.push_back(new HomedFrog(this, getTexture(TextureName::FROG), Point2D<int>(116, 23)));
	nests.push_back(new HomedFrog(this, getTexture(TextureName::FROG), Point2D<int>(212, 23)));
	nests.push_back(new HomedFrog(this, getTexture(TextureName::FROG), Point2D<int>(308, 23)));
	nests.push_back(new HomedFrog(this, getTexture(TextureName::FROG), Point2D<int>(404, 23)));

	logs.push_back(new Log(this, getTexture(TextureName::LOG2), Point2D<int>(-100, 60), Vector2D<float>(72.6, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG2), Point2D<int>(75, 60), Vector2D<float>(72.6, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG2), Point2D<int>(250, 60), Vector2D<float>(72.6, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG2), Point2D<int>(425, 60), Vector2D<float>(72.6, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG2), Point2D<int>(370, 121), Vector2D<float>(96, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG1), Point2D<int>(460, 121), Vector2D<float>(96, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG2), Point2D<int>(120, 121), Vector2D<float>(96, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG1), Point2D<int>(210, 121), Vector2D<float>(96, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG2), Point2D<int>(-130, 121), Vector2D<float>(96, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG1), Point2D<int>(-40, 121), Vector2D<float>(96, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG1), Point2D<int>(30, 153), Vector2D<float>(48, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG1), Point2D<int>(180, 153), Vector2D<float>(48, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG1), Point2D<int>(330, 153), Vector2D<float>(48, 0)));
	
	//temporales
	logs.push_back(new Log(this, getTexture(TextureName::LOG2), Point2D<int>(0, 185), Vector2D<float>(48, 0)));
	logs.push_back(new Log(this, getTexture(TextureName::LOG2), Point2D<int>(0, 90), Vector2D<float>(48, 0)));

	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE1), Point2D<int>(50, 372), Vector2D<float>(-48, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE1), Point2D<int>(200, 372), Vector2D<float>(-48, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE1), Point2D<int>(350, 372), Vector2D<float>(-48, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE2), Point2D<int>(25, 342), Vector2D<float>(48, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE2), Point2D<int>(175, 342), Vector2D<float>(48, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE2), Point2D<int>(325, 342), Vector2D<float>(48, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE3), Point2D<int>(175, 312), Vector2D<float>(-72, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE3), Point2D<int>(325, 312), Vector2D<float>(-72, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE3), Point2D<int>(475, 312), Vector2D<float>(-72, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE4), Point2D<int>(150, 280), Vector2D<float>(48, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE4), Point2D<int>(0, 280), Vector2D<float>(48, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE4), Point2D<int>(-150, 280), Vector2D<float>(48, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE5), Point2D<int>(165, 252), Vector2D<float>(-72, 0.0)));
	vehicles.push_back(new Vehicle(this, getTexture(TextureName::VEHICLE5), Point2D<int>(365, 252), Vector2D<float>(-72, 0.0)));

	timeUntilWasp = getRandomRange(1000, SDL_GetTicks() + 1000);
	waspDestructionTime = SDL_GetTicks() + timeUntilWasp;

	// Render la primera vez.
	render();

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Game::~Game()
{
	delete player;
	for (int i = 0; i < logs.size(); i++) {
		delete logs[i];
	}
	for (int i = 0; i < vehicles.size(); i++) {
		delete vehicles[i];
	}
	for (int i = 0; i < nests.size(); i++) {
		delete nests[i];
	}
	for (size_t i = 0; i < textures.size(); i++) {
		delete textures[i];
	}
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	getTexture(TextureName::BACKGROUND)->render();

	player->render();

	for (int i = 0; i < logs.size(); i++) {
		logs[i]->render();
	}
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->render();
	}
	for (const auto& w : wasps) {
		w->render();
	}
	for (const auto& hFrog : nests) {
		if (hFrog->isHome()) {
			hFrog->render();
		}
	}

	SDL_RenderPresent(renderer);

}

void
Game::update()
{
	player->update();
	for (int i = 0; i < logs.size(); i++) {
		logs[i]->update();
	}
	for (int i = 0; i < vehicles.size(); i++) {
		vehicles[i]->update();
	}

	currentTime = SDL_GetTicks();

	if (currentTime >= waspDestructionTime) {
		int nestNr = getRandomRange(0, waspPositions.size() - 1);
		wasps.push_back(new Wasp(this, getTexture(TextureName::WASP), Point2D<int>(waspPositions[nestNr].getX(), 25), Vector2D<float>(0, 0), getRandomRange(1000, 10000)));
		timeUntilWasp = getRandomRange(1000, SDL_GetTicks() + 1000);
		waspDestructionTime = currentTime + timeUntilWasp;
	}
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
		startTime = SDL_GetTicks();
		handleEvents();
		update();
		render();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE) {
			SDL_Delay(FRAME_RATE - frameTime);
		}
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
		else if (event.type == SDL_EVENT_KEY_DOWN) {
			player->handleEvent(event);
		}
	}
}

Collision
Game::checkCollision(const SDL_FRect& rect) const
{
	Collision col{ Collision::NONE, {0,0} };
	for (const auto& l : logs) {
		col = l->checkCollision(rect);
		if (col.type != Collision::NONE) {
			break;
		}
	}
	if (col.type != Collision::NONE) {
		return col;
	}

	for (const auto& v : vehicles) {
		col = v->checkCollision(rect);
		if (col.type != Collision::NONE) {
			break;
		}
	}
	if (col.type != Collision::NONE) {
		return col;
	}

	for (const auto& w : wasps) {
		col = w->checkCollision(rect);
		if (col.type != Collision::NONE) {
			break;
		}
	}
	if (col.type != Collision::NONE) {
		return col;
	}
	for (const auto& n : nests) {
		col = n->checkCollision(rect);
		if (col.type != Collision::NONE) {
			break;
		}
	}
	return col;
}

int Game::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<int>(min, max)(randomGenerator);
}
